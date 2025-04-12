modded class rag_baseitems_carlift
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