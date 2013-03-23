#include "patientEditDialog.h"
#include <QTextCodec>
#include <QTextStream>

patientEditDialog::patientEditDialog( QWidget *parent, pacient* pat, PoliclinicDatabase& database )
    : pat(pat), QDialog(parent), database(database)
{
    ui.setupUi(this);

    QByteArray fio(pat->fio), work(pat->work), address(pat->addres);
    //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    QString fioString = codec->toUnicode(fio);
    QString addressString = codec->toUnicode(address);
    QString workString = codec->toUnicode(work);

    ui.nameEdit->setText( fioString );
    ui.addressEdit->setText( addressString );
    ui.workEdit->setText( workString );
    ui.yearEdit->setText( QString::number(pat->birth) );

    QString numberStr;
    numberStr.sprintf("%02i %06i", pat->number.okrug, pat->number.num);
    ui.idEdit->setText( numberStr );
}

patientEditDialog::~patientEditDialog()
{
}

void patientEditDialog::done(int accepted)
{
    if (accepted > 0)
    {
        fioChanged();
        addressChanged();
        workChanged();
        idChanged();
        yearChanged();
    }
    QDialog::done(accepted);
}

void patientEditDialog::fioChanged()
{
    //QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    QByteArray fio = codec->fromUnicode( ui.nameEdit->text() );
    strncpy_s( pat->fio, fio.constData(), 50 );
}

void patientEditDialog::addressChanged()
{
    //QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    QByteArray address = codec->fromUnicode( ui.addressEdit->text() );
    strncpy_s( pat->addres, address.constData(), 50 );
}

void patientEditDialog::workChanged()
{
    //QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    QByteArray work = codec->fromUnicode( ui.workEdit->text() );
    strncpy_s( pat->work, work.constData(), 50 );
}

void patientEditDialog::idChanged()
{
    QString id = ui.idEdit->text();
    QTextStream stream(&id);
    stream >> pat->number.okrug >> pat->number.num;
}

void patientEditDialog::yearChanged()
{
    QString year = ui.yearEdit->text();
    pat->birth = year.toInt();
}
  