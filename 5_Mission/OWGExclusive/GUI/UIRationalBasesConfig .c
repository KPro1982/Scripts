class UIRationalBasesConfig extends UIScriptedMenu
{
	
	UIScriptedMenu m_Parent;
    private bool                 m_Initialized;
    private bool                 m_IsMenuOpen;

    //---Elements from .layout file

    private ButtonWidget         m_CloseButton;
	private ButtonWidget         m_OkButton;
	
	private EditBoxWidget		 m_ContainerMaxEditBox;
	private EditBoxWidget		 m_CodeLockMaxEditBox;
	private EditBoxWidget		 m_RadiusEditBox;
		
    //---

    //Array that stores child widgets we create during runtime
    //private ref array<ref Widget> m_CustomChildrenHighIQ;

    void UIRationalBasesConfig()
    {
		
    }

    /*
		This is the destructor, called when this class is deleted / destroyed
    */
    void ~UIRationalBasesConfig() 
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

		m_ContainerMaxEditBox.SetText(RB_GetKonfig().max_containers.ToString());
		m_CodeLockMaxEditBox.SetText(RB_GetKonfig().max_locks.ToString());
		m_RadiusEditBox.SetText(RB_GetKonfig().search_radius.ToString());
		
		
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

    }

    override Widget Init()
    {
        if (!m_Initialized) //Only draw and init widgets if not already done that, since this function is called each time you do ( ShowScriptedMenu() )
        {
            layoutRoot = GetGame().GetWorkspace().CreateWidgets( "OWGExclusive/scripts/GUI/Layouts/KPRationalBasesConfig.layout");
            
            //Define elements from .layout ( you must cast each element to its according script class if you wish to use its functions see scripts\1_Core\proto\EnWidgets.c )

			m_CloseButton    = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "close_button" ) );
			m_OkButton    = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ok_button" ) );

			m_ContainerMaxEditBox = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "containermax_editbox" ) );
			m_CodeLockMaxEditBox = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "codelockmax_editbox" ) );
			m_RadiusEditBox = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "radius_editbox" ) );
			

									
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
				int rbmc = m_ContainerMaxEditBox.GetText().ToInt();
				RB_GetKonfig().max_containers = rbmc;
				string rbmlstr = m_CodeLockMaxEditBox.GetText();
				int rbml = rbmlstr.ToInt();
				RB_GetKonfig().max_locks = rbml;
				RB_GetKonfig().search_radius = m_RadiusEditBox.GetText().ToInt();
				RB_GetKonfig().Save();
				Close();					
    		break;
			
			case m_CloseButton:
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