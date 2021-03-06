#ifndef BAG_COMPOUNDLAYERDESCRIPTOR_H
#define BAG_COMPOUNDLAYERDESCRIPTOR_H

#include "bag_compoundlayer.h"
#include "bag_config.h"
#include "bag_fordec.h"
#include "bag_layerdescriptor.h"
#include "bag_types.h"

#include <memory>


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)  // std classes do not have DL-interface when exporting
#endif

namespace BAG {

//! Describe a compound layer.
class BAG_API CompoundLayerDescriptor final : public LayerDescriptor
{
public:
    static std::shared_ptr<CompoundLayerDescriptor> create(Dataset& dataset,
        const std::string& name, DataType indexType,
        RecordDefinition definition, uint64_t chunkSize,
        int compressionLevel);
    static std::shared_ptr<CompoundLayerDescriptor> open(Dataset& dataset,
        const std::string& name);

    CompoundLayerDescriptor(const CompoundLayerDescriptor&) = delete;
    CompoundLayerDescriptor(CompoundLayerDescriptor&&) = delete;

    CompoundLayerDescriptor& operator=(const CompoundLayerDescriptor&) = delete;
    CompoundLayerDescriptor& operator=(CompoundLayerDescriptor&&) = delete;

    std::weak_ptr<Dataset> getDataset() const &;
    const RecordDefinition& getDefinition() const & noexcept;

protected:
    CompoundLayerDescriptor(Dataset& dataset, const std::string& name,
        DataType indexType, RecordDefinition definition, uint64_t chunkSize,
        int compressionLevel);

private:
    DataType getDataTypeProxy() const noexcept override;
    uint8_t getElementSizeProxy() const noexcept override;

    const std::string& getValuesPath() const & noexcept;

    //! The dataset this layer is from.
    std::weak_ptr<Dataset> m_pBagDataset;
    //! The data type (depends on layer type).
    DataType m_dataType = DT_UNKNOWN_DATA_TYPE;
    //! The size of a single index in the HDF5 file.
    uint8_t m_elementSize = 0;
    //! The list of fields making up the record.
    RecordDefinition m_definition;
    //! The path to the values.
    std::string m_valuesPath;

    friend CompoundLayer;
};

}  // namespace BAG

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif  // BAG_COMPOUNDLAYERDESCRIPTOR_H

