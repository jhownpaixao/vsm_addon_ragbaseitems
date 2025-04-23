modded class rag_baseitems_placeable_base : ItemBase
{
    protected bool m_LastOpen;
    void rag_baseitems_placeable_base()
    {
        VSM_StartAutoClose();
    }

    //! mesclar caracteristicas do storage para virtual
    override bool CanPutInCargo(EntityAI parent)
    {
        if(!VSM_CanVirtualize() || !VSM_HasVirtualItems())
            return super.CanPutInCargo(parent)

        return false;
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        if(!VSM_CanVirtualize() || !VSM_HasVirtualItems())
            return super.CanPutIntoHands(parent)

        return false;
    }

    override bool CanReceiveItemIntoCargo(EntityAI item)
    {
        if (VSM_CanManipule())
            return super.CanReceiveItemIntoCargo(item);

        return false;
    }

    override bool CanReleaseCargo(EntityAI cargo)
    {
        if (VSM_CanManipule())
            return super.CanReleaseCargo(cargo);

        return false;
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        //!desativar por enquanto, está impedindo a criação de attachments mesmo vindo do módulo de virtualização
        //TODO: formular um método de criação dos attachments apartir do módulo, ao mesmo tempo que não permite o player mexer...
        if (VSM_IsOpen() /* && !VSM_IsProcessing() */) 
            return super.CanReceiveAttachment(attachment, slotId);

        return false;
    }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        if (VSM_CanManipule())
            return super.CanReleaseAttachment(attachment);

        return false;
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (VSM_CanManipule())
            return super.CanDisplayAttachmentSlot(slot_id);

        return false;
    }

    override bool CanDisplayCargo()
    {
        if (VSM_CanManipule())
            return super.CanDisplayCargo();

        return false;
    }

     bool CanDisplayAttachmentCategory( string category_name )
	{
		if (VSM_IsOpen())
            return super.CanDisplayAttachmentCategory(category_name);

        return false;
	}

    override void Open()
    {
        if(VSM_IsProcessing())
            return;
            
        super.Open();
        if (GetGame().IsServer())
        {
            VirtualStorageModule.GetModule().OnLoadVirtualStore(this);
            VSM_StartAutoClose();
        }
            
    }

    override void Close()
    {
        if(VSM_IsProcessing())
            return;

        if (GetGame().IsServer())
        {
            VirtualStorageModule.GetModule().OnSaveVirtualStore(this);
            VSM_StopAutoClose();
        }
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

    override void OnDamageDestroyed(int oldLevel)
	{
		super.OnDamageDestroyed(oldLevel);
		if (GetGame().IsServer())
            VirtualStorageModule.GetModule().OnDestroyed(this);
	};

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
        super.VSM_OnAfterContainerRestore(); //autoclose ?
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