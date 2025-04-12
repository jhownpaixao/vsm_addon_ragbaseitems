modded class rag_baseitems_smoker
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
