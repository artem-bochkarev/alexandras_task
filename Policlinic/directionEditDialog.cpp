#include "directionEditDialog.h"
#include <QTextCodec>
#include <QTextStream>
#include <QMessageBox>

directionEditDialog::directionEditDialog( QWidget *parent, direction* dir, PoliclinicDatabase& database )
    : dir(dir), QDialog(parent), database(database)
{
    ui.setupUi(this);

    QObject::connect( ui.specialityComboBox, SIGNAL(currentIndexChanged(int)),
        this, SLOT(specialityChecked(int)) );

    QObject::connect( ui.nameComboBox, SIGNAL(currentIndexChanged(int)),
        this, SLOT(doctorChecked(int)) );

    QObject::connect( ui.areaComboBox, SIGNAL(currentIndexChanged(int)),
        this, SLOT(areaChecked(int)) );

    QObject::connect( ui.numberComboBox, SIGNAL(currentIndexChanged(int)),
        this, SLOT(numberChecked(int)) );

    QTextCodec *codec = QTextCodec::codecForName("CP866"); 

    std::list<std::string> specs = database.getDoctorsSpecialities();
    std::list<std::string>::iterator iter = specs.begin();
    for ( ;iter != specs.end(); ++iter)
    {
        QByteArray spec(iter->c_str());
        ui.specialityComboBox->addItem(codec->toUnicode(spec));
    }

    std::list<int> okrugs = database.getAreas();
    std::list<int>::iterator it = okrugs.begin();
    for ( ;it != okrugs.end(); ++it)
    {
        ui.areaComboBox->addItem( QString::number(*it) );
    }

    if ( dir != 0 )
    {
        const doctor* doc = database.getDoctorByDirection(*dir);
        if ( doc != 0 )

        {
            QByteArray spec(doc->dolgnost);
            findAndSet( ui.specialityComboBox, codec->toUnicode(spec) );
        }

        QByteArray fio(dir->fio);
        findAndSet( ui.nameComboBox, codec->toUnicode(fio) );

        findAndSet( ui.areaComboBox, QString::number(dir->number.okrug) );        
        findAndSet( ui.numberComboBox, QString::number(dir->number.num) );
    }
}

directionEditDialog::~directionEditDialog()
{
}

void directionEditDialog::findAndSet( QComboBox* comboBox, QString& str )
{
    int index = comboBox->findText(str);
    if ( index != -1 )
        comboBox->setCurrentIndex(index);
}

void directionEditDialog::done(int accepted)
{
    if (accepted > 0)
    {
        if ( (area < 0) || (number < 0) || (currentDoctor.length() < 1) || (currentSpec.length() < 1))
        {
            QMessageBox msgBox;
            msgBox.setText(tr("Something not entered"));
            msgBox.setInformativeText(tr("Do you want to exit without saving?"));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();
            if ( ret == QMessageBox::Cancel )
                return;
        }else
        {
            direction d;
            d.number.okrug = area;
            d.number.num = number;
            strncpy_s( d.fio, currentDoctor.c_str(), 50 );
            QString time = ui.timeEdit->time().toString("hh:mm");
            QTextCodec *codec = QTextCodec::codecForName("CP866");
            QByteArray tim = codec->fromUnicode( time );
            strncpy_s( d.time, tim.constData(), 10 );

            QString date = ui.dateEdit->date().toString("dd.MM.yyyy");
            QByteArray dat = codec->fromUnicode( date );
            strncpy_s( d.date, dat.constData(), 20 );
            if (dir == 0)
            {
                database.getDirections().add(d);
            }else
            {
                *dir = d;
            }
        }
    }
    QDialog::done(accepted);
}

void directionEditDialog::specialityChecked(int index)
{
    std::list<std::string> specs = database.getDoctorsSpecialities();
    std::list<std::string>::iterator iter = specs.begin();
    for ( int i=0;i != index; ++i)
        ++iter;

    currentSpec = *iter;
    std::list<doctor> doctors;
    database.getDoctors().searchDolg(currentSpec.c_str(), doctors);

    QTextCodec *codec = QTextCodec::codecForName("CP866"); 
    ui.nameComboBox->clear();
    std::list<doctor>::iterator it = doctors.begin();
    for ( ;it != doctors.end(); ++it)
    {
        QByteArray fio(it->fio);
        ui.nameComboBox->addItem(codec->toUnicode(fio));
    }
}

void directionEditDialog::doctorChecked(int index)
{
    currentDoctor = "";
    if ( index >= 0 )
    {
        std::list<doctor> doctors;
        database.getDoctors().searchDolg(currentSpec.c_str(), doctors);

        std::list<doctor>::iterator it = doctors.begin();
        for ( int i=0;i<index; ++i)
            ++it;
        ui.cabinetLabel->setText(QString::number(it->cabinet));
        currentDoctor = it->fio;
    }
}

void directionEditDialog::areaChecked(int index)
{
    area = -1;
    if ( index >= 0 )
    {
        QString str = ui.areaComboBox->itemText(index);
        area = str.toInt();

        std::list<int> numbers = database.getNumbers(area);
        ui.numberComboBox->clear();
        std::list<int>::iterator it = numbers.begin();
        for ( ;it!=numbers.end(); ++it)
            ui.numberComboBox->addItem( QString::number(*it) );
    }
}

void directionEditDialog::numberChecked(int index)
{
    number = -1;
    if ( index >= 0 )
    {
        QString str = ui.numberComboBox->itemText(index);
        number = str.toInt();

        reg_num rNum;
        rNum.okrug = area;
        rNum.num = number;

        const pacient* p = database.getPatients().getID(rNum);
        if ( p != 0 )
        {
            QTextCodec *codec = QTextCodec::codecForName("CP866");
            QByteArray fio(p->fio);
            ui.patientNameLabel->setText(codec->toUnicode(fio));
        }
    }
}
  