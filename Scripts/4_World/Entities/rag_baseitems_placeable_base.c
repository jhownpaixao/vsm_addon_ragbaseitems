modded class rag_baseitems_placeable_base : ItemBase
{
    protected bool m_LastOpen;

    //Behaviour overrides----------------------------------------
    override bool CanPutInCargo(EntityAI parent)
    {
        if(super.CanPutInCargo(parent))
        {
            if(!IsShelfCrate() && VSM_CanVirtualize() && VSM_HasVirtualItems())
                return false;

            return true;
        }
        
        return false;
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        if(super.CanPutIntoHands(parent))
        {
            if(!IsShelfCrate() && VSM_CanVirtualize() && VSM_HasVirtualItems())
                return false;

            return true;
        }
        
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
        if (VSM_CanManipule()) 
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
                VirtualStorageModule.GetModule().OnSaveVirtualStore(this);
            }
            
            super.Close();
        }
    }


    //VSM adjustments----------------------------------------
    override bool VSM_IsOpen()
    {
        return IsOpen();
    }

    override void VSM_Open()
    {
        super.VSM_Open();

        if (VSM_CanOpen())
        {
            Open();
        }
    }

    override void VSM_Close()
    {
        super.VSM_Close();
    
        if (VSM_CanClose())
        {
            Close();
        }
    }

    override bool VSM_IsVirtualizable()
    {
        if(super.VSM_IsVirtualizable())
            return !GetInventory().IsAttachment();
        
        return false;
    }

    //VSM Wrapper events ----------------------------------------
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
        if(VirtualStorageModule.GetModule().IsRemoving()) return;

        ctx.Write(m_VSM_HasVirtualItems);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version)) return false;

        //TODO este seria o certo, mas os servers em produção ainda não tem este recurso e vão falhar
        //TODO primeiro lançar uma att com ele, e na proxima desativa-lo
		// if(VSM_Addon_RaGBaseItems.GetAddon().IsNew()) return true; 

        if (!ctx.Read(m_VSM_HasVirtualItems)) return false;

        return true;
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad(); // se for por primeiro abre/fecha o container e atrapalha o fluxo
        VSM_SetHasItems(m_VSM_HasVirtualItems);
    }
}