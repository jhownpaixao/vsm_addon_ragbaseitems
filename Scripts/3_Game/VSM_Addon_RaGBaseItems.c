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
        /**
        * @note: Durante a primeira implementação dos addons
        * todos os addons acabaram usando o vanilla addon como base, por tanto
        * não estarão devidamente registrados e com isso gera script corrupted,
        * pois mesmo já presentes, a versão será a inicial.
        * Pensando neste ponto, a versão inicial do addon foi alterada.
        * //!@warning: REMOVER ISSO NA PROXIMA ATT
        */

        if(VSM_Version.GetManager().HasAddon("VSM_Addon_Vanilla"))
        {
            return VSMAddonRaGBaseItems_StorageVersion.V_1509;
        }
        else
        {
            return VSMAddonRaGBaseItems_StorageVersion.V_0000;
        }
        
        // return VSMAddonRaGBaseItems_StorageVersion.V_0000;
    }

    override protected int GetVersion()
    {
        return VSMAddonRaGBaseItems_StorageVersion.CURRENT_VERSION;
    }
};