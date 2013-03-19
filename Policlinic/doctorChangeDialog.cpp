#include "doctorChangeDialog.h"
#include <QTextCodec>

doctorChangeDialog::doctorChangeDialog( QWidget *parent, doctor* doc )
    : doc(doc), QDialog(parent)
{
    ui.setupUi(this);

    QByteArray fio(doc->fio), dolgnost(doc->dolgnost), work(doc->priem);
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QString fioString = codec->toUnicode(fio);
    QString dolgnostString = codec->toUnicode(dolgnost);
    QString workString = codec->toUnicode(work);
    ui.fio->setText( fioString );
    ui.cabinet->setText( QString::number( doc->cabinet ) );
    ui.speciality->setText( dolgnostString );
    ui.workHours->setText( workString );
}

doctorChangeDialog::~doctorChangeDialog()
{
}

void doctorChangeDialog::done(int accepted)
{
    if (accepted > 0)
    {
        fioChanged();
        dolgnostChanged();
        workChanged();
        cabinetChanged();
    }
    QDialog::done(accepted);
}

void doctorChangeDialog::fioChanged()
{
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QByteArray fio = codec->fromUnicode( ui.fio->text() );
    strncpy_s( doc->fio, fio.constData(), 50 );
}

void doctorChangeDialog::dolgnostChanged()
{
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QByteArray dolgnost = codec->fromUnicode( ui.speciality->text() );
    strncpy_s( doc->dolgnost, dolgnost.constData(), 50 );
}

void doctorChangeDialog::workChanged()
{
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QByteArray work = codec->fromUnicode( ui.workHours->text() );
    strncpy_s( doc->priem, work.constData(), 50 );
}

void doctorChangeDialog::cabinetChanged()
{
    QString cab = ui.cabinet->text();
    doc->cabinet = cab.toInt();
}
  