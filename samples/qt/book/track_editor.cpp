#include <ivl/ivl>
#include <ivl/qt>
#include "track_editor.hpp"

using namespace qt_book;

int main(int argc, char *argv[])
{
    application app(argc, argv);

    vector <track> tracks;
    tracks.push_back(track("The Flying Dutchman: Overture", 630));
    tracks.push_back(track("The Flying Dutchman: Wie aus der Fern laengst vergangner Zeiten", 374));
    tracks.push_back(track("The Flying Dutchman: Steuermann, lass die Wacht", 152));
    tracks.push_back(track("Die Walkuere: Ride of the Valkyries", 286));
    tracks.push_back(track("Tannhaeuser: Freudig begruessen wir die edle Halle", 384));
    tracks.push_back(track("Tannhaeuser: Wie Todesahnung - O du mein holder Abendstern", 257));
    tracks.push_back(track("Lohengrin: Treulich gefuert ziehet dahnin", 294));
    tracks.push_back(track("Lohengrin: In fernem Land", 383));
    tracks.push_back(track("Die Meistersinger von Nuernberg: Overture", 543));
    tracks.push_back(track("Die Meistersinger von Nuernberg: Verachtet mir die Meister nicht", 200));
    tracks.push_back(track("Die Meistersinger von Nuernberg: Ehrt eure deutschen Meister", 112));
    tracks.push_back(track("Goetterdaemmerung: Funeral Music", 469));
    tracks.push_back(track("Tristan und Isolde: Mild und leise, wie er laechelt", 375));;

    track_editor editor(tracks);
    editor.resize(600, 300);
    editor.show();

    return app.exec();
}
