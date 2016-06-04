#include <QCoreApplication>
#include <QTextStream>
#include <QtCore>
#include <QFile>
#include <QString>

QString Read(QString);
void Write(QString, QString);

int main(int argc, char *argv[])
{
    QStringList dados;
    QStringList linhas[100];
    QString rawdados;

    double id[100];
    double tempoespera[100];
    double tempoChegada[100];
    double tempoProcessamento[100];
    double tempoOcios;
    double tempoOcup;
    double tempoMTurnA;
    double tempoMProcessamento;

    QCoreApplication a(argc, argv);
    rawdados = Read("C:/Users/Natan Lima/Desktop/All/Ufrn/16.1/SO/processos.dat");
    dados = rawdados.split("\n");

    tempoOcios = 0;
    tempoOcup = 0;
    tempoMTurnA = 0;
    tempoMProcessamento = 0;

    for(int i=0;i<100;i++){
        tempoProcessamento[i] = 0;
        id[i] = 0;
        tempoChegada[i] = 0;
        tempoespera[i] = 0;
    }

    for(int j = 0; j<100;j++){
    linhas[j] = dados[j].split(" ");
    }

        for(int i = 0; i<100; i++){
        tempoChegada[i] = linhas[i][1].toDouble();
        id[i] = linhas[i][0].toDouble();
        int aux = 3;
        tempoOcios += tempoChegada[i];

        for(int j = 0; j < linhas[i][2].toInt(); j++){
        tempoProcessamento[i] = tempoProcessamento[i] + (linhas[i][aux].toDouble());
        aux++;
        }

        tempoProcessamento[i] = tempoProcessamento[i] + (((linhas[i][2].toDouble()) -1)*10);
        tempoMProcessamento += tempoProcessamento[i]/100;
        tempoProcessamento[i] = tempoProcessamento[i] + tempoChegada[i];
        tempoMTurnA += tempoProcessamento[i]/100;
        tempoOcup += tempoProcessamento[i];
        }

        double tempoMespera;
        tempoMespera = 0;

        for(int i=1; i<100;i++){
            tempoespera[i] = tempoChegada[i] + tempoProcessamento[i-1] + tempoespera[i-1];
            tempoMespera += tempoespera[i]/100;

        }
        qDebug() << tempoMTurnA;
        qDebug() << tempoMProcessamento;
        qDebug() << tempoMespera;
        qDebug() << tempoOcios;
        qDebug() << tempoOcup;



        int ordem,aux1=0,aux2=0;
        ordem=99;
        while (ordem>0){
        for (int i=0;i<ordem; i++){
        if (tempoProcessamento[i]>tempoProcessamento[i+1]){
        //aux3= id[i];
        aux2=tempoProcessamento[i];
        aux1 = tempoChegada[i];
        //id[i]=id[i+1];
        tempoChegada[i]=tempoChegada[i+1];
        tempoChegada[i+1]=aux1;
        tempoProcessamento[i]=tempoProcessamento[i+1];
        tempoProcessamento[i+1]=aux2;
        //id[i+1]=aux3;
        }
        }
        ordem=ordem-1;
        }

        for(int i=0;i<100;i++){
            tempoMProcessamento += (tempoProcessamento[i] - tempoChegada[i])/100;
            tempoMTurnA += tempoProcessamento[i]/100;

            tempoOcup += tempoProcessamento[i];
        }
        //int espera;
        for(int i=1; i<100;i++){
            //espera=id[i];
            tempoespera[i] = tempoChegada[i] + tempoProcessamento[i-1] + tempoespera[i-1];
            tempoMespera += tempoespera[i]/100;
        }

        qDebug() << id[0];
        qDebug()<< tempoProcessamento[0];
        qDebug() << tempoMTurnA;
        qDebug() << tempoMProcessamento;
        qDebug() << tempoMespera;
        qDebug() << tempoOcios;
        qDebug() << tempoOcup;


    return a.exec();
    }


    QString Read(QString Filename)
    {
        QFile mFile(Filename);

        if(!mFile.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() <<"Não consegui abrir o arquivo para escrita";
            return 0;
        }
        QTextStream in(&mFile);
        QString mText = in.readAll();

        mFile.close();
        return mText;
    }

    void Write(QString Filename, QString Texto){
        QFile mFile(Filename);

        if(!mFile.open(QFile::WriteOnly | QFile::Text))
        {
            qDebug() <<"Não consegui abrir o arquivo para escrita";
            return;
        }

        QTextStream out(&mFile);
        out << Texto;
        mFile.flush();
        mFile.close();
    }
