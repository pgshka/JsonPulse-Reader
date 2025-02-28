[BaseContainerProps(), SCR_ContainerActionTitle()]
class JPRC_RestartMission : JPR_Command
{
	override void Init(notnull array<ref V30_Json_Value> args)
	{
		Print("Restart mission");
	}
}