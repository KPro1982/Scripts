class OWG_Konfig
{

	protected static string ConfigPATH = "$profile:\\OWGExclusive\\Config_settings.json";
	private static const string configRoot = "$profile:\\OWGExclusive\\";	
/////////////////////////////////////////////////////////////////////////////////////////////////////	
// Variables to save go here
//
	string ConfigVersion = "1";
	ref array<ref string> AdminSteamIDs = {};
	
	
// NonSerialed Variables that should not be saved go here
	[NonSerialized()]
	int ConfigInt = 1;

	
	
//////////////////////////////////////////////////////////////////////////////////////////////////
	
	void OWG_Konfig()
	{
	
		AdminSteamIDs = new array<ref string>;
		AdminSteamIDs.Insert("76561198413492901");
		AdminSteamIDs.Insert("76561198063590739");
		
		
	
	
	}
	
	void Load(){
		Print("[OWGExclusive] Loading Config");
		if (GetGame().IsServer()){
			
			if (FileExist(configRoot)==0) // Save Directory Does not Exist
	        {
	            Print("[OWGExclusive] '" + configRoot + "' does not exist, creating directory");
	            MakeDirectory(configRoot);
	        }
			
			if (FileExist(ConfigPATH)){ //If Config File exist load File
			    JsonFileLoader<OWG_Konfig>.JsonLoadFile(ConfigPATH, this);
				if (ConfigVersion != "1"){
					ConfigVersion = "1";
					Save();
				}
			}else{ //File does not exist create file
				Save();
			}
		}
	}
	
	void Save(){
		JsonFileLoader<OWG_Konfig>.JsonSaveFile(ConfigPATH, this);
	}
	
	bool ValidatePermissions(string steamId)
	{
		for(int i = 0; i < AdminSteamIDs.Count(); i++)
		{
			if (steamId == AdminSteamIDs.Get(i))
			{
				return true;
			}
		
		
		}
		
		return false;
	
	}

		
}
ref OWG_Konfig m_OWG_Konfig;

//Helper function to return Config
static ref OWG_Konfig OWG_GetKonfig()
{
	if (!m_OWG_Konfig)
	{
		m_OWG_Konfig = new OWG_Konfig;
			
		if ( GetGame().IsServer() ){
			m_OWG_Konfig.Load();
		}
	}
	return m_OWG_Konfig;
};
