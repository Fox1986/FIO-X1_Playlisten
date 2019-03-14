#include <iostream>
#include <fstream>
#include <dirent.h>

using namespace std;

void headline (string titel)
{
    char star = '*';
    int len  = titel.length();
    for (int s = 0; s <=len; s++){
        cout << star;
    }
    cout << "\n";
    cout << titel << endl;
    for (int s = 0; s <=len; s++){
        cout << star;
    }
    cout << "\n" << endl;
}


int main()
{
    bool durchlauf = true;
    do{
        string titel =  "Dieses Programm passt die FOOBAR2000-Playlists dem FIIOX1-Format an";
        headline(titel);

        //zeige alle verfügbaren Dateien in dem Ordner. Das soll die Eingabe erleichtern.
        cout << "Vorhandene Playlists: " << endl;
        DIR *hdir;
        struct dirent *entry;

        hdir = opendir(".");
        do {
            entry = readdir(hdir);
            if (entry){
                cout << entry->d_name << endl;
            }
        } while (entry);
        closedir(hdir);

        //Ab hier wird die eigentliche Konvertierung gestartet.
        ifstream input;
        ofstream output;
        string reader, playlist;

        cout << "Bitte zu konvertierende m3u-Datei eingeben (ohne Dateityp): ";
        cin >> playlist;
        // Es wird eine zweite Playlist erstellt, damit die alte für FOOBAR2000 erhalten bleibt und weiter genutzt werden kann.
        input.open(playlist+".m3u", ios::in);
        output.open(playlist+"_FX1.m3u", ios::out|ios::app);
        while (!input.eof()){
            getline(input, reader);
            reader.erase(0,21); // Findet den allgemeinen Pfad bis zu den Genre-Ordnern
            reader.erase(0,reader.find("\\"));   //Löscht den Genre-Ordner, sodass nur noch Interpreten etc. übrig bleiben
            reader.insert(0,".."); //Dadurch ist es Möglich die Playlists in einem eigenen Ordner zu lagern.
            output << reader << "\n";
        }
        cout << "Playlist in " << playlist << "_FX1.m3u konvertiert!" << endl;
        input.close();
        output.close();

        //Schleife wiederholen?
        char frage;
        cout << "Weitere Playlisten? j/n : ";
        cin >> frage;
        if (frage != 'j')
            durchlauf = false;
    } while(durchlauf);

    return 0;
}
