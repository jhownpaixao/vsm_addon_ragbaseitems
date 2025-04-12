modded class rag_baseitems_ammo_cleaner
{
    override bool VSM_CanVirtualize()
    {
        return false;
    }
    
    override bool VSM_IsOpen()
    {
        return true;
    } 
}