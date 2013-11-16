#include "MenusAndIcons.c"

task main()
{
	TIconIndex icon = iconNone;
	string iconStr = "";
	StringFormat(iconStr, "0x%0.2X", icon);
	drawMenu(menuFromRight, icon, icon, icon, iconStr, "");

	while ( true ) {
		switch (nNxtButtonTransition)
		{
		case kEnterButton:
		case kExitButton:
			return;
			break;
		case kRightButton:
			icon++;
			StringFormat(iconStr, "0x%0.2X", icon);
			drawMenu(menuFromRight, icon, icon, icon, iconStr, "");
			break;
		case kLeftButton:
			icon--;
			StringFormat(iconStr, "0x%0.2X", icon);
			drawMenu(menuFromRight, icon, icon, icon, iconStr, "");
			break;
		}
	}
}
