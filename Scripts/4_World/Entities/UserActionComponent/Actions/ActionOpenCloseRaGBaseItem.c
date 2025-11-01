modded class ActionOpenCloseRaGBaseItem
{
	override void OnStartServer( ActionData action_data )
	{
		ItemBase building = ItemBase.Cast(action_data.m_Target.GetObject());
		if (building)		
		{
			if (building.IsOpen())
			{
				if (building.VSM_IsVirtualStorage() && !building.VSM_CanClose())
				{
					VirtualUtils.SendMessageToPlayer(action_data.m_Player, "STR_VSM_NOT_CLOSE_CONTAINER");
					return;
				}
				building.Close();
			}
			else
			{
				if (building.VSM_IsVirtualStorage() && !building.VSM_CanOpen())
				{
					VirtualUtils.SendMessageToPlayer(action_data.m_Player, "STR_VSM_NOT_OPEN_CONTAINER");
					return;
				}
				building.Open();
			}
		}
	}
};