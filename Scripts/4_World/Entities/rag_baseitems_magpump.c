modded class rag_baseitems_magpump
{
    override void VSM_Close()
    {
        if (!IsPumpActive())
        {
            VSM_StartAutoClose();
            return;
        }

        super.VSM_Close();
    }
}