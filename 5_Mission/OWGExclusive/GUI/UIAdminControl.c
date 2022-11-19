class UIAdminControl extends UIScriptedMenu
{
	
	ref UIRationalVehiclesConfig KPRationalVehiclesConfigMenu;  
	ref UIRationalBasesConfig KPRationalBasesConfigMenu; 
	
    private bool                 m_Initialized;
    private bool                 m_IsMenuOpen;

    //---Elements from .layout file

    private ButtonWidget         m_CloseButton;
	private ButtonWidget         m_OkButton;
	
	private CheckBoxWidget		 m_RationalBasesCheckBox;
    private ButtonWidget		 m_RationalBasesConfigButton;
	
	private CheckBoxWidget		 m_VehiclesCheckBox;
    private ButtonWidget		 m_VehiclesConfigButton;
	
	private CheckBoxWidget		 m_CompassCheckBox;
	private CheckBoxWidget		 m_GPSCheckBox;
	private CheckBoxWidget		 m_ShowCarKillsCheckBox;
	private CheckBoxWidget		 m_ShowAllKillsCheckBox;
		
    //---

    //Array that stores child widgets we create during runtime
    //private ref array<ref Widget> m_CustomChildrenHighIQ;

    void UIAdminControl()
    {
       /*Do something when this class is created. This is the constructor, it is the very firt thing called out of all other methods.
    		More info on Enforce syntax and functionality here:  https://community.bistudio.com/wiki/DayZ:Enforce_Script_Syntax
    	*/
    	//m_CustomChildrenHighIQ = new array<ref Widget>;
    }

    /*
		This is the destructor, called when this class is deleted / destroyed
    */
    void ~UIAdminControl() 
    {
        PPEffects.SetBlurMenu( 0 );
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );

        //Destroy root widget and all its children
        if ( layoutRoot )
        	layoutRoot.Unlink();
    }

    //after show
    override void OnShow()
    {
        super.OnShow();
		KPMenuUtils.LockControls();
        PPEffects.SetBlurMenu( 0.5 ); //Add blurr effect
		m_CompassCheckBox.SetChecked(RC_GetKonfig().RequireCompass);
		m_VehiclesCheckBox.SetChecked(RV_GetKonfig().RationalVehiclesActive);
		m_GPSCheckBox.SetChecked(RG_GetKonfig().RequireGPS);
		m_ShowAllKillsCheckBox.SetChecked(RV_GetKonfig().AllKillCount);
		m_ShowCarKillsCheckBox.SetChecked(RV_GetKonfig().CarKillCountOnly);
		m_RationalBasesCheckBox.SetChecked(RB_GetKonfig().RationalBasesActive);		
		
		
    }

    //after hide
    override void OnHide()
    {
        super.OnHide();
        PPEffects.SetBlurMenu( 0 ); //Remove blurr effect

        //Unlock controls, this also happens in missionGameplay.c however including it here will assure control is gained back incase that method is not invoked. 
        //That can occur when other mods / scripts force a menu on screen illegally 
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
		KPMenuUtils.UnlockControls();
    }

    override Widget Init()
    {
        if (!m_Initialized) //Only draw and init widgets if not already done that, since this function is called each time you do ( ShowScriptedMenu() )
        {
            layoutRoot = GetGame().GetWorkspace().CreateWidgets( "OWGExclusive/scripts/GUI/Layouts/KPAdminControl.layout");
            
            //Define elements from .layout ( you must cast each element to its according script class if you wish to use its functions see scripts\1_Core\proto\EnWidgets.c )

			m_CloseButton    = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "close_button" ) );
			m_OkButton    = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ok_button" ) );

			m_RationalBasesCheckBox = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "rationalbases_checkbox" ) );
			m_RationalBasesConfigButton = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "rationalbasesconfig_button" ) );
	
			m_VehiclesCheckBox = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "vehicles_checkbox" ) );
    		m_VehiclesConfigButton = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "vehiclesconfig_button" ) );
	
		
			m_CompassCheckBox = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "compass_checkbox" ) );
			m_GPSCheckBox = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "gps_checkbox" ) );
			m_ShowCarKillsCheckBox = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "showcarkills_checkbox" ) );
			m_ShowAllKillsCheckBox = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "showallkills_checkbox" ) );
			
			
			
						
          //  WidgetEventHandler.GetInstance().RegisterOnDoubleClick( m_Grid, this, "OnDoubleClicked" ); //Attach a double-click event on a specifc widget
          //  WidgetEventHandler.GetInstance().RegisterOnDoubleClick( m_Scroller, this, "OnDoubleClicked" );

            m_Initialized = true;
        }
        return layoutRoot;
    }

   

    //Called on each frame, this will be paused when the menu is hidden or missiongameplay callqueue is frozen / paused
    override void Update(float timeslice)
    {
        super.Update(timeslice);

    }

    //Click event triggers when you click on a widget, this method wont get called if your widget has the "IgnorePointer" property toggled in your .layout
    override bool OnClick(Widget w, int x, int y, int button)
    {
    	switch(w)
    	{

    		case m_OkButton:
				GetGame().GetUIManager().HideScriptedMenu(this);					
    		break;
			
			case m_CloseButton:
				GetGame().GetUIManager().HideScriptedMenu(this);
			break;
			
			case m_CompassCheckBox:
					RC_GetKonfig().SetRequireCompass(m_CompassCheckBox.IsChecked());				
			break;
		
			case m_GPSCheckBox:
				RG_GetKonfig().SetRequireGPS(m_GPSCheckBox.IsChecked());
			break;
			
			case m_ShowCarKillsCheckBox:
					RV_GetKonfig().SetCarKillCountOnly(m_ShowCarKillsCheckBox.IsChecked());
			
				
			break;
			
			case m_ShowAllKillsCheckBox:
					RV_GetKonfig().SetAllKillCount(m_ShowAllKillsCheckBox.IsChecked());

				
			break;
			
			case m_VehiclesCheckBox:
					RV_GetKonfig().SetRationalVehiclesActive(m_VehiclesCheckBox.IsChecked());
				
			break;
			
			case m_RationalBasesCheckBox:
					RB_GetKonfig().SetRationalBasesActive(m_RationalBasesCheckBox.IsChecked());
				
			break;
			
			case m_VehiclesConfigButton:
				KPRationalVehiclesConfigMenu = UIRationalVehiclesConfig.Cast(GetGame().GetUIManager().EnterScriptedMenu(UI_RV_CONFIG, this));
                KPRationalVehiclesConfigMenu.SetMenuOpen(true);

				
			break;
			
			case m_RationalBasesConfigButton:
				KPRationalBasesConfigMenu = UIRationalBasesConfig.Cast(GetGame().GetUIManager().EnterScriptedMenu(UI_RB_CONFIG, this));
                KPRationalBasesConfigMenu.SetMenuOpen(true);

				
			break;
				
			
    	}
        return super.OnClick(w, x, y, button);
    }

    //Called by WidgetEventHandler that is registered at line 70 ( more of these examples can be found in vanilla scripts / menus creates by devs )
    void OnDoubleClicked(Widget w, int x, int y, int button) 
    {
        if (button == MouseState.LEFT)
        {
            //Do something
        }
        else if (button == MouseState.RIGHT)
        {
            //Do something
        }
    }

    bool IsMenuOpen() 
    {
        return m_IsMenuOpen;
    }

    void SetMenuOpen(bool isMenuOpen) 
    {
        m_IsMenuOpen = isMenuOpen;
        if (m_IsMenuOpen)
            PPEffects.SetBlurMenu( 0.5 );
        else
            PPEffects.SetBlurMenu( 0 );
    }
};