modded class MissionServer extends MissionBase
{
	override void OnInit() {
		super.OnInit();
		
		Print("[OWG_OWGExclusive] OnInit");
		OWG_GetKonfig();
		GetRPCManager().AddRPC( "OWG_OWGExclusive", "RPCOWG_Konfig", this, SingeplayerExecutionType.Both );
	}
	
	void RPCOWG_Konfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		PlayerIdentity RequestedBy = PlayerIdentity.Cast(sender);
		if (RequestedBy){
			GetRPCManager().SendRPC("OWG_OWGExclusive", "RPCOWG_Konfig", new Param1< OWG_Konfig >( OWG_GetKonfig() ), true, RequestedBy);
			Print("#########config requested");
		}
	}
}


