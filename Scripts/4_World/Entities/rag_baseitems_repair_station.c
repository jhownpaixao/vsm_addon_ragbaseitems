modded class rag_baseitems_repair_station
{
    override void VSM_Close()
    {
        if (m_IsGrindStoneSpinning)
        {
            VSM_StartAutoClose();
            return;
        }

        super.VSM_Close();
    }
}