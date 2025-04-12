modded class rag_baseitems_table_saw
{
    override void VSM_Close()
    {
        if (m_IsSawTableRunning)
        {
            VSM_StartAutoClose();
            return;
        }

        super.VSM_Close();
    }
}