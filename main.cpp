#include <QtCore/QCoreApplication>
#include <QDir>
#include <QDebug>
#include <vector>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <QFile>

const QString target_root = "/media/harsh/Entertainment/Entertain here!!!/Mu$!c Gallery/albums/";

void categorise(QString root){
    QDir obj(root);

    QStringList name_filters;
    name_filters << "*";

    QStringList d_contents = obj.entryList(name_filters, QDir::AllDirs|QDir::NoDotAndDotDot);

    qDebug()<<"Searching Directories in "<<root<<endl;
    for(int i=0; i<d_contents.size(); ++i){
        qDebug()<<"Entering "<<d_contents[i]<<endl;
        categorise(root+"/"+d_contents[i]);
        qDebug()<<"Exiting "<<d_contents[i]<<endl<<"***************************"<<endl;
    }

    qDebug()<<"Searching Files in "<<root<<endl;

    QStringList name_filter_2;
    name_filter_2 << "*.mp3";

    QStringList f_contents = obj.entryList(name_filter_2, QDir::Files);

    for(int i=0; i<f_contents.size(); ++i){
        QFile mp3file(root+"/"+f_contents[i]);

        TagLib::FileRef f(QFile::encodeName(root+"/"+f_contents[i]).constData());
        QString album_name = TStringToQString(f.tag()->album());
        if(album_name==""){
            album_name = obj.dirName();
        }
        QDir new_folder(target_root+album_name);
        if(new_folder.exists()==false){
            new_folder.mkdir(target_root+album_name);
        }
        mp3file.rename(target_root+album_name+"/"+f_contents[i]);
        qDebug()<<"Moved "<<f_contents[i]<<" in "<<album_name<<endl;
    }

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    //declaring variables
    QString dir_root = "/media/harsh/Entertainment/Entertain here!!!/Mu$!c Gallery";

    QDir target_dir(target_root);
    if(target_dir.exists()==false)
        target_dir.mkdir(target_root);

    categorise(dir_root);

    return a.exec();
}
