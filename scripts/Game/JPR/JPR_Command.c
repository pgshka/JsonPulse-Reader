[BaseContainerProps(), SCR_ContainerActionTitle()]
class JPR_Command : ScriptAndConfig
{
	
	[Attribute("command.example", UIWidgets.EditBox, "")]
	string m_sName;
	
	[Attribute(desc: "")]
	bool m_bEnabled;

	void Init(notnull array<ref V30_Json_Value> args)
	{
		PrintFormat("JPR [%1] %1 - Executed", this, m_sName);
	}
	
	string GetArg(notnull array<ref V30_Json_Value> args, int index)
		return args.Get(index).AsString().Get();
}