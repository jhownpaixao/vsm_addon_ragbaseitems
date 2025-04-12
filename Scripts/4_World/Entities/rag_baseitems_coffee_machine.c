modded class rag_baseitems_coffee_machine
{
    override void VSM_Close()
    {
        if (m_IsEspressoRunning || m_IsCoffeeRunning)
        {
            VSM_StartAutoClose();
            return;
        }

        super.VSM_Close();
    }
}