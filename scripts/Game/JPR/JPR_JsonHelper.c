class JPR_JsonHelper
{	
	static V30_Json_array GetConfig(string path)
	{
		auto jsonConfig = V30_Json_FileDeserializer(path).Deserialize();
		if (!jsonConfig || jsonConfig.IsNull())
			return null;
		
		return jsonConfig.AsArray();
	}
}