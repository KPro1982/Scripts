class UIRationalVehiclesConfig extends UIScriptedMenu
{
    private bool                 m_Initialized;
    private bool                 m_IsMenuOpen;

    //---Elements from .layout file

    private ButtonWidget         m_CloseButton;
	private ButtonWidget         m_OkButton;
	
	private EditBoxWidget		 m_MinimumDamageEditBox;
	private EditBoxWidget		 m_DamageEditBox;
		
    //---

    //Array that stores child widgets we create during runtime
    //private ref array<ref Widget> m_CustomChildrenHighIQ;

    void UIRationalVehiclesConfig()
    {
       /*Do something when this class is created. This is the constructor, it is the very firt thing called out of all other methods.
    		More info on Enforce syntax and functionality here:  https://community.bistudio.com/wiki/DayZ:Enforce_Script_Syntax
    	*/
    	//m_CustomChildrenHighIQ = new array<ref Widget>;
    }

    /*
		This is the destructor, called when this class is deleted / destroyed
    */
    void ~UIRationalVehiclesConfig() 
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

		m_DamageEditBox.SetText(RV_GetKonfig().DamageModifierPercentage.ToString());
		m_MinimumDamageEditBox.SetText(RV_GetKonfig().MinimumDamagePercentage.ToString());
		
		
		
    }

    //after hide
    override void OnHide()
    {
        super.OnHide();
        PPEffects.SetBlurMenu( 0 ); //Remove blurr effect
		KPMenuUtils.UnlockControls();


        //Unlock controls, this also happens in missionGameplay.c however including it here will assure control is gained back incase that method is not invoked. 
        //That can occur when other mods / scripts force a menu on screen illegally 

		// GetParentMenu().EnterScriptedMenu(UI_ADMIN_CONTROL);
    }

    override Widget Init()
    {
        if (!m_Initialized) //Only draw and init widgets if not already done that, since this function is called each time you do ( ShowScriptedMenu() )
        {
            layoutRoot = GetGame().GetWorkspace().CreateWidgets( "OWGExclusive/scripts/GUI/Layouts/KPRationalVehiclesConfig.layout");
            
            //Define elements from .layout ( you must cast each element to its according script class if you wish to use its functions see scripts\1_Core\proto\EnWidgets.c )

			m_CloseButton    = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "close_button" ) );
			m_OkButton    = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ok_button" ) );

			m_MinimumDamageEditBox = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "minimumdamage_editbox" ) );
			m_DamageEditBox = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "damage_editbox" ) );
									
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
				RV_GetKonfig().SetDamageModifierPercentage(m_DamageEditBox.GetText().ToInt());
				RV_GetKonfig().SetMinimumDamagePercentage(m_MinimumDamageEditBox.GetText().ToInt());
				KPMenuUtils.UnlockControls();
				Close();			
    		break;
			
			case m_CloseButton:
        //		GetGame().GetUIManager().HideScriptedMenu(this);
		//		GetGame().GetUIManager().EnterScriptedMenu(UI_ADMIN_CONTROL, null);
				KPMenuUtils.UnlockControls();
				Close();
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