modded class MissionServer extends MissionBase
{
	override void OnInit() 
	{
		super.OnInit();
		
		Print("[OWG_OWGExclusive] OnInit");
		OWG_GetKonfig();

		
		GetRPCManager().AddRPC( "OWG_OWGExclusive", "RPCOWG_Konfig", this, SingeplayerExecutionType.Both );
		GetRPCManager().AddRPC( "OWG_OWGExclusive", "RPCOWG_Update", this, SingeplayerExecutionType.Both );
	}
		// Server responds to client request
	void RPCOWG_Konfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) 
	{
		PlayerIdentity RequestedBy = PlayerIdentity.Cast(sender);
		if (RequestedBy){
			GetRPCManager().SendRPC("OWG_OWGExclusive", "RPCOWG_Konfig", new Param1< OWG_Konfig >( OWG_GetKonfig() ), true, RequestedBy);
			Print("#########config requested");
		}	
			
	}
		
	// Server responds to client update request
	void RPCOWG_Update( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) 
	{		
		Param1< OWG_Konfig > data;
		if ( !ctx.Read( data ) ) return;
		Print("########[OWG_ServerSave][Client] Received Config From Server");
		m_OWG_Konfig = data.param1;
		m_OWG_Konfig.Save();
	}
	
}


