modded class rag_baseitems_container_base
{
    protected bool m_LastOpen;

    void rag_baseitems_container_base()
    {
        VSM_StartAutoClose();
    }

    //! mesclar caracteristicas do storage para virtual
    override bool CanPutInCargo(EntityAI parent)
    {
        if (!super.CanPutInCargo(parent))
            return false;

        if(VSM_CanVirtualize())
            return !m_VSM_HasVirtualItems;

        return true;
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        if (!super.CanPutIntoHands(parent))
            return false;

        if(VSM_CanVirtualize())
            return !m_VSM_HasVirtualItems;
        
        return true;
    }

    override void Open()
    {
        super.Open();
        if (GetGame().IsServer())
        {
            VirtualStorageModule.GetModule().OnLoadVirtualStore(this);
            VSM_StartAutoClose();
        }
    }

    override void Close()
    {
        
        if (GetGame().IsServer())
        {
            VirtualStorageModule.GetModule().OnSaveVirtualStore(this);
            VSM_StopAutoClose();
        }
        
        // Print("CLOSE CHAMADO PARA " + GetType());
        super.Close();
    }

    //! virtualização
    override bool VSM_IsOpen()
    {
        return IsOpen();
    }

    override void VSM_Open()
    {
        super.VSM_Open();

        if (VSM_CanVirtualize() && !VSM_IsOpen())
        {
            Open();
        }
    }

    override void VSM_Close()
    {
        super.VSM_Close();
    
        if (VSM_CanVirtualize() && VSM_IsOpen())
        {
            Close();
        }
    }

    override void EEInit()
	{
        super.EEInit();

		if (GetGame().IsServer())
        {
            VirtualStorageModule.GetModule().OnInitContainer(this);
        }
	}

    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);

        if (GetGame().IsServer())
            VirtualStorageModule.GetModule().OnDeleteContainer(this);
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_VSM_HasVirtualItems);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        ctx.Read(m_VSM_HasVirtualItems)

        return true;
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad(); // se for por primeiro abre/fecha o container e atrapalha o fluxo
        VSM_SetHasItems(m_VSM_HasVirtualItems);
    }

    override void VSM_OnBeforeRestoreChildren() //as item
    {
        SetStateOpen()
    }

    override void VSM_OnAfterRestoreChildren() // as item
    {
        RestoreStateOpen();
    }

    override void VSM_OnBeforeContainerRestore() // as storage
    {
        SetStateOpen()
    }

    override void VSM_OnAfterContainerRestore() // as storage
    {
        super.VSM_OnAfterContainerRestore(); //autoclose
        RestoreStateOpen();
    }

    void SetStateOpen()
    {
        m_LastOpen = m_IsOpened;
        m_IsOpened = true;
    }

    void RestoreStateOpen() // as item
    {
        m_IsOpened = m_LastOpen;
    }

}