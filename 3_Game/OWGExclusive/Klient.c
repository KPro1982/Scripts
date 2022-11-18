class OWG_Klient
{

	private static string ConfigSettingsPATH = "$profile:\\OWGExclusiveConfig\\Client_settings.json";
	private static string configRoot = "$profile:\\OWGExclusiveConfig\\";	

	string ConfigVersion = "2";
	string m_hello = "Hello World";
	
	void Load(){
		if (GetGame().IsClient() || !GetGame().IsMultiplayer()){
			
			if (FileExist(configRoot)==0) // Save Directory Does not Exist
	        {
	            Print("[OWGExclusiveConfig] '" + configRoot + "' does not exist, creating directory");
	            MakeDirectory(configRoot);
	        }
			
			
			
			
			if (FileExist(ConfigSettingsPATH)){ //If config exist load File
			    JsonFileLoader<OWG_Klient>.JsonLoadFile(ConfigSettingsPATH, this);
				if (ConfigVersion != "2"){
					ConfigVersion = "2";
					Save();
				}
			}
		}
	}
	
	void Save(){
		JsonFileLoader<OWG_Klient>.JsonSaveFile(ConfigSettingsPATH, this);
	}
	
	
	
}


static ref OWG_Klient m_OWG_Klient;

//Helper function to return Config
static OWG_Klient OWG_GetKlient()
{
	if (!m_OWG_Klient)
	{
		m_OWG_Klient = new OWG_Klient;
			
		if ( !GetGame().IsServer() ){
			m_OWG_Klient.Load();
		}
	}
	return m_OWG_Klient;
};
