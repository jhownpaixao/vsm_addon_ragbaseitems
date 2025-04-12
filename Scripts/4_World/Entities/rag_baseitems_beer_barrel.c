modded class rag_baseitems_beer_barrel
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