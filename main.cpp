#include <QDebug>
#include <QApplication>
#include <QObject>
#include <QTextStream>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
//    qWarning("Hello console!");

//    QString msg("This is a qt string");
//    int x = 20;

//    QTextStream out(stdout);
//    out.setFieldWidth(20);
//    out.setPadChar('*');
//    out << msg << x << "hotov";

    auto msg1 = QObject::tr("Hello my friend.");
    auto msg2 = (QObject::tr("Goodbye"));

    QTextStream out_stream(stdout);

    out_stream << msg1 << "\n" << msg2 << endl;

    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
