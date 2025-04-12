modded class rag_baseitems_magpump
{
    override void VSM_Close()
    {
        if (m_IsMagPumpRunning)
        {
            VSM_StartAutoClose();
            return;
        }

        super.VSM_Close();
    }
}