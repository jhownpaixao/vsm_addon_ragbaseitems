modded class rag_baseitems_weapon_cleaner
{
    override void VSM_Close()
    {
        if (m_IsWeaponCleanerRunning)
        {
            VSM_StartAutoClose();
            return;
        }

        super.VSM_Close();
    }
}