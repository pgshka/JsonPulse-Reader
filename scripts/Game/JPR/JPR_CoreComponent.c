[EntityEditorProps(category: "GameScripted/GameMode", description: "")]
class JPR_CoreComponentClass : SCR_BaseGameModeComponentClass
{
}

class JPR_CoreComponent : SCR_BaseGameModeComponent
{
	protected static const float CHECK_PERIOD = 5;
	protected static const string FILE_PATH = "$profile:JPR/temp.json";
	
	protected float m_fCheckDelay;
	
	[Attribute(UIWidgets.Auto)]
	ref array<ref JPR_Command> m_aCommands;
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{		
		if (Replication.IsServer() && !SCR_Global.IsEditMode()) {
			SetEventMask(owner, EntityEvent.INIT);
			SetEventMask(owner, EntityEvent.FRAME);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		ArmaReforgerScripted game = GetGame();
		if (game && !game.InPlayMode())
			return;
		
		if (!FileIO.FileExists(FILE_PATH)) {
			PrintFormat("JPR-Core: Missing config file, it should be at '$profile:JPR/temp.json'.", level: LogLevel.ERROR);
			return;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		super.EOnFrame(owner, timeSlice);
		m_fCheckDelay -= timeSlice;
		if (m_fCheckDelay <= 0)
		{
			m_fCheckDelay = CHECK_PERIOD;
			V30_Json_array list = JPR_JsonHelper.GetConfig(FILE_PATH);
			if (list) {
				foreach (V30_Json_Value value : list.Get()) {
					ProcessCommand(value);
				}
				
				list.Get().Clear();
				V30_Json_FileSerializer(FILE_PATH).Serialize(list);
			}
		}
	}
	
	void ProcessCommand(notnull V30_Json_Value value)
	{
		Print("JPR: proccess command");
		if (!value.IsObject()) 
			return;
		
		V30_Json_object command = value.AsObject();
		string name = command.GetAt("name").AsString().Get();
		array<ref V30_Json_Value> args = command.GetAt("args").AsArray().Get();
		
		foreach (JPR_Command com : m_aCommands)
		{
			if (com.m_sName == name)
				com.Init(args);
		}
	}
}
