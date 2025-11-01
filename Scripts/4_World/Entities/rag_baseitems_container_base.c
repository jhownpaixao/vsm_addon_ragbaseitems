modded class rag_baseitems_container_base
{
    protected bool m_LastOpen;

    void rag_baseitems_container_base()
    {
        VSM_StartAutoClose();
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

    override bool CanDisplayAttachmentCategory( string category_name )
	{
		if (VSM_IsOpen())
            return super.CanDisplayAttachmentCategory(category_name);

        return false;
	}

    override void Open()
    {   
        if (VSM_CanOpen())
        {
            super.Open();

            if (GetGame().IsServer())
            {
                VSM_StartAutoClose();
                VirtualStorageModule.GetModule().OnLoadVirtualStore(this);
            }
        }
    }

    override void Close()
    {
        if (VSM_CanClose())
        {
            if (GetGame().IsServer())
            {
                VSM_StopAutoClose();
                VirtualStorageModule.GetModule().OnSaveVirtualStore(this);
            }
            
            super.Close();
        }
    }

    //! virtualização
    override bool VSM_IsOpen()
    {
        return IsOpen();
    }

    override void VSM_Open()
    {
        super.VSM_Open();
        if (!VSM_IsOpen())
        {
            Open();
        }
    }

    override void VSM_Close()
    {
        super.VSM_Close();

        if (VSM_IsOpen())
        {
           	Close();
        };
    }

    override void EEInit()
	{
        super.EEInit();

		if (GetGame().IsServer())
            VirtualStorageModule.GetModule().OnInitContainer(this);
        
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

        if(!VirtualStorageModule.GetModule().IsNew())
            ctx.Write(m_VSM_HasVirtualItems);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if(!VirtualStorageModule.GetModule().IsRemoving())
            ctx.Read(m_VSM_HasVirtualItems);

        return true;
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad(); // se for por primeiro abre/fecha o container e atrapalha o fluxo
        
        VSM_SetHasItems(m_VSM_HasVirtualItems);
    }

    //! compatibilidade---------------------------------------------------
    override void VSM_OnBeforeRestoreChildren() 
    {
        super.VSM_OnBeforeRestoreChildren();

        //! abrir para restauarar os filhos (senão bloqueia)
        m_LastOpen = m_IsOpened;
        m_IsOpened = true;
    }

    override void VSM_OnAfterRestoreChildren() 
    {   
        super.VSM_OnAfterRestoreChildren();

        //! restaurar o estado anterior
        m_IsOpened = m_LastOpen;
    }

    override void VSM_OnBeforeVirtualize()
    {
        super.VSM_OnBeforeVirtualize();
        
        if (!VSM_IsOpen() && VSM_HasVirtualItems()) 
            VSM_Open();
    }
    //! ---------------------------------------------------

    override bool VSM_IsVirtualizable()
    {
        if(super.VSM_IsVirtualizable())
            return !GetInventory().IsAttachment();
        
        return false;
    }
}