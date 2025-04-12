class CfgPatches
{
	class vsm_addon_ragbaseitems
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"VSM_Core", "rag_baseitems_scripts"};
	};
};

class CfgMods
{
	class VSM_Addon_RaGBaseItems
	{
		dir = "vsm_addon_ragbaseitems";
		picture = "";
		action = "";
		hideName = 0;
		name = "VSM RaG Base Items Addon";
		hidePicture = 0;
		credits = "Jhonnata Paixão";
		author = "iTzChronuZ";
		authorID = "76561199441861559";
		version = "1.0.0";
		extra = 0;
		type = "mod";
		dependencies[]= {"World"};

		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"vsm_addon_ragbaseitems/Scripts/4_World"};
			};
		};
	};
};