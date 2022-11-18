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
	
		
	private void LockControls()
    {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor( true );
        GetGame().GetMission().GetHud().Show( false );
    }

    private void UnlockControls()
    {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetMission().GetHud().Show( true );
    }
	
	

	override void OnUpdate(float timeslice)
	{        		
		super.OnUpdate(timeslice); 		
		if ( GetGame().GetInput().LocalPress("OWGAdmin") && GetGame().GetUIManager().GetMenu() == NULL ) 
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
                    UnlockControls();
                } else if (GetGame().GetUIManager().GetMenu() == NULL) {
                    //Show Menu
                    GetGame().GetUIManager().ShowScriptedMenu(KPAdminControlMenu, NULL);
                    KPAdminControlMenu.SetMenuOpen(true);
                    LockControls();
                }
            } else if (GetGame().GetUIManager().GetMenu() == NULL && KPAdminControlMenu == null) {
                //Create Menu
                LockControls();
                KPAdminControlMenu = UIAdminControl.Cast(GetUIManager().EnterScriptedMenu(UI_ADMIN_CONTROL, null));
				KPAdminControlMenu.SetMenuOpen(true);

            }
							
								
		} 
			
	}
	
	
	
	
}
