    #ifndef CTRPLUGINFRAMEWORK_OSD_HPP
#define CTRPLUGINFRAMEWORK_OSD_HPP

#include "CTRPluginFramework/Graphics/Color.hpp"

#include <string>

namespace CTRPluginFramework
{
    class OSD
    {

    public:
        /*
        ** OSD::Notify
        ** Send a notification on the top screen, a notification duration is 5 seconds
        ** A maximum of 50 notifications can be queued
        ** Parameters:
        **  str : text of the notification
        **  foreground : the color of the text (Default: blank)
        **  background : the color of the background (Default: black)
        ** Return value!
        **  0 : Success
        **  -1 : Failed to add the notification
        **********************************************************/

        static int      Notify(std::string str, Color foreground = Color(255, 255, 255), Color background = Color());

        /*
        ** OSD::WriteLine
        ** Allows you to write a line of text on the screen while the game's running
        ** Parameters:
        **  screen: on which screen you want to draw : 0 : Bottom, 1 : Top
        **  line : the text you want to draw
        **  posX : where to start the drawing
        **  posY : where ti start the drawing
        **  foreground : color of the text (Default: blank)
        **  background : color of the background (Default : black)
        ************************************************************/
        static void     WriteLine(int screen, std::string line, int posX, int posY, Color foreground = Color(255, 255, 255), Color background = Color());
		/*
		** OSD::WriteLine
		** Allows you to write a line of text on the screen while the game's running
		** Parameters:
		**  screen: on which screen you want to draw : 0 : Bottom, 1 : Top
		**  line : the text you want to draw
		**  posX : where to start the drawing
		**  posY : where ti start the drawing
		**  offset3d : the offset of posX for the right eye
		**  foreground : color of the text (Default: blank)
		**  background : color of the background (Default : black)
		************************************************************/
		static void     WriteLine(int screen, std::string line, int posX, int posY, int offset3d, Color foreground = Color(255, 255, 255), Color background = Color());

    };
}

#endif
