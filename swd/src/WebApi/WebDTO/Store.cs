using Domain.Models;

namespace WebApi.WebDTO;

public class StoreInfoWDTO(string name, string ogrn)
{
    public string Name { get; init; } = name;
    public string Ogrn { get; init; } = ogrn;

    public StoreInfo WDTOtoDDTO()
    {
        var storeInfo = new StoreInfo(Name, Ogrn);
        return storeInfo;
    }
}