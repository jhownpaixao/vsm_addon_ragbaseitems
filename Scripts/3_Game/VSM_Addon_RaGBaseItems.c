class VSM_Addon_RaGBaseItems extends VSMAddonBase
{
    protected static ref VSM_Addon_RaGBaseItems m_Instance;

    void VSM_Addon_RaGBaseItems( int index, string path )
    {
        m_Instance = this;
    }

    static VSM_Addon_RaGBaseItems GetAddon()
    {
        return m_Instance;
    }

	override protected string GetAddonId()
    {   
        return "VSM_Addon_RaGBaseItems";
    }
    
    override protected int GetInitVersion()
    {
        return VSMAddonRaGBaseItems_StorageVersion.V_0000;
    }

    override protected int GetVersion()
    {
        return VSMAddonRaGBaseItems_StorageVersion.CURRENT_VERSION;
    }
};