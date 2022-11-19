modded class MissionGameplay
{   
		 ref UIAdminControl KPAdminControlMenu;

	

		override void OnMissionStart()
	{
		super.OnMissionStart();
		OWG_GetKlient();
		GetRPCManager().AddRPC( "OWG_OWGExclusive", "RPCOWG_Konfig", this, SingeplayerExecutionType.Both );
		Print("#########[OWG_OWGExclusive][Client] Requesting Config From Server");
		GetRPCManager().SendRPC("OWG_OWGExclusive", "RPCOWG_Konfig", new Param1< OWG_Konfig >( NULL ), true, NULL);
	}
	
	
	void RPCOWG_Konfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param1< OWG_Konfig > data;
		if ( !ctx.Read( data ) ) return;
		Print("########[OWG_OWGExclusive][Client] Received Config From Server");
		m_OWG_Konfig = data.param1;
	}
	
		

	
	

	override void OnUpdate(float timeslice)
	{        		
		super.OnUpdate(timeslice); 	
		
		bool kpress = GetGame().GetInput().LocalPress("OWGAdmin");
		if(GetGame().GetUIManager().GetMenu() == NULL)
		{
			bool gmenu = true;
			KPMenuUtils.UnlockControls();
			
		}
		
		if ( kpress && gmenu) 
		{				
			string curSteamId = GetGame().GetUserManager().GetTitleInitiator().GetUid();
			if(!OWG_GetKonfig().ValidatePermissions(curSteamId))
			{
				return;  // not a valid admin
			}
			if ( KPAdminControlMenu ) {
                if (KPAdminControlMenu.IsMenuOpen()) {
                    //Hide Menu
                    KPAdminControlMenu.SetMenuOpen(false);
                    GetGame().GetUIManager().HideScriptedMenu(KPAdminControlMenu);
                    KPMenuUtils.UnlockControls();
                } else if (GetGame().GetUIManager().GetMenu() == NULL) {
                    //Show Menu
                    GetGame().GetUIManager().ShowScriptedMenu(KPAdminControlMenu, NULL);
                    KPAdminControlMenu.SetMenuOpen(true);
                    KPMenuUtils.LockControls();
                }
            } else if (GetGame().GetUIManager().GetMenu() == NULL && KPAdminControlMenu == null) {
                //Create Menu
                KPMenuUtils.LockControls();
                KPAdminControlMenu = UIAdminControl.Cast(GetUIManager().EnterScriptedMenu(UI_ADMIN_CONTROL, null));
				KPAdminControlMenu.SetMenuOpen(true);

            }
							
								
		} 
			
	}
	
	
	
	
}
