#include <QCoreApplication>
#include <QTextStream>
#include <QtCore>
#include <QFile>
#include <QString>

//Função para ler o arquivo
QString Read(QString);
// Função para escrever um arquivo
void Write(QString, QString);

int main(int argc, char *argv[])
{
    QStringList dados;
    QStringList linhas[100];
    QString rawdados;


    double id[100];
    // Vetor que quarda o tempo de espera de cada processo
    double tempoespera[100];
    // Vetor que guarda o tempo de chegada a CPU de cada processo
    double tempoChegada[100];
    // Vetor que guarda os tempos de processamento de cada processo
    double tempoProcessamento[100];
    // Variavel do tempo onde a CPU ficou ociosa
    double tempoOcios;
    // Variavel que guarda o tempo onde a CPU ficou ocupada
    double tempoOcup;
    // Tempo médio de TurnAround
    double tempoMTurnA;
    // Tempo médio de processamento
    double tempoMProcessamento;
    // Taxa percentual de ocupação da CPU
    double TaxaOcup;
    // Taxa percentual de ociosidade da CPU
    double TaxaOcios;
    // Tempo total
    double tempoTotal;

    QCoreApplication a(argc, argv);
    rawdados = Read("C:/Users/Natan Lima/Desktop/All/Ufrn/16.1/SO/processos.dat");
    dados = rawdados.split("\n");

    //FCFS

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
        tempoOcup += tempoProcessamento[i];
        tempoProcessamento[i] = tempoProcessamento[i] + tempoChegada[i];



        }

        double tempoMespera;
        tempoMespera = 0;


        for(int i=1; i<100;i++){
            tempoespera[i] = tempoChegada[i] + tempoProcessamento[i-1] + tempoespera[i-1];
            tempoMespera += tempoespera[i]/100;
        }

        for(int i=0;i<100;i++){
            tempoMTurnA += (tempoProcessamento[i] + tempoespera[i])/100;
        }
        tempoTotal = tempoOcios + tempoOcup;
        TaxaOcios= (tempoOcios/tempoTotal)*100;
        TaxaOcup= (tempoOcup/tempoTotal)*100;


        qDebug() << tempoTotal;
        qDebug() << TaxaOcios;
        qDebug() << TaxaOcup;
        qDebug() << tempoMTurnA;
        qDebug() << tempoMProcessamento;
        qDebug() << tempoMespera;
        qDebug() << tempoOcios;
        qDebug() << tempoOcup;


    //SJF
        int ordem,aux1=0,aux2=0;
        ordem=99;
        while (ordem>0){
            for (int i=0;i<ordem; i++){
                if (tempoProcessamento[i]>tempoProcessamento[i+1]){
                    aux2=tempoProcessamento[i];
                    aux1 = tempoChegada[i];
                    tempoChegada[i]=tempoChegada[i+1];
                    tempoChegada[i+1]=aux1;
                    tempoProcessamento[i]=tempoProcessamento[i+1];
                    tempoProcessamento[i+1]=aux2;
                    }
            }
            ordem=ordem-1;
        }

        tempoOcup=0;
        tempoMProcessamento=0;
        tempoMTurnA=0;

        for(int i=0;i<100;i++){

            tempoMProcessamento += (tempoProcessamento[i]-tempoChegada[i])/100;
            tempoOcup += (tempoProcessamento[i]-tempoChegada[i]);
        }
        tempoMespera=0;
        tempoespera[0]=tempoChegada[0];
        for(int i=1; i<100;i++){
            tempoespera[i] = tempoChegada[i] + tempoProcessamento[i-1] + tempoespera[i-1];
            tempoMespera += tempoespera[i]/100;
        }

        for(int i=0;i<100;i++){
            tempoMTurnA += (tempoProcessamento[i] + tempoespera[i])/100;
        }
        
        qDebug() << tempoTotal;
        qDebug() << TaxaOcios;
        qDebug() << TaxaOcup;
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
            qDebug() <<"Não consegui abrir o arquivo para leitura";
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

