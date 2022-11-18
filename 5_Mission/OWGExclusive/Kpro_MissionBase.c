modded class MissionBase {
    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu) {
            switch (id) {
            case UI_ADMIN_CONTROL:
                menu = new UIAdminControl;
                break;
            
            case UI_RV_CONFIG:
                menu = new UIRationalVehiclesConfig;
                break;
				
			case UI_RB_CONFIG:
                menu = new UIRationalBasesConfig;
                break;	
				
            }			
			
			
			
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}
