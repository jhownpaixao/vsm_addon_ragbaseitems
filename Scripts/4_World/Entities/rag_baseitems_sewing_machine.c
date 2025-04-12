modded class rag_baseitems_sewing_machine
{
    protected bool m_ForceRestore;

    override void VSM_Close()
    {
        if (m_IsSewingMachineRunning)
        {
            VSM_StartAutoClose();
            return;
        }

        super.VSM_Close();
    }

    override void VSM_OnBeforeContainerRestore() // as storage
    {
        super.VSM_OnBeforeContainerRestore();
        m_ForceRestore = true;
    }

    override void VSM_OnAfterContainerRestore() // as storage
    {
        super.VSM_OnBeforeContainerRestore();
        m_ForceRestore = false;
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if(m_ForceRestore)
        return true;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}