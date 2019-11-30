#include "Reader.h"

class Column : public ORCIterator
{
  private:
    uint64_t columnIndex;
    uint64_t numOfRows;
    std::unique_ptr<orc::ColumnStatistics> stats;
    std::unique_ptr<orc::BloomFilterIndex> bloomFilter;
    int64_t typeKind;
    const Stripe& stripe;
    orc::ColumnVectorBatch* selectedBatch;

    bool testBloomFilter(py::object);
    const orc::Type* findColumnType(const orc::Type*);
    orc::ColumnVectorBatch* selectBatch(const orc::Type&, orc::ColumnVectorBatch*);

  public:
    Column(const Stripe&, uint64_t, std::map<uint32_t, orc::BloomFilterIndex>);
    bool contains(py::object);
    bool hasNull() const;
    uint64_t numberOfValues() const;
    uint64_t len() const override;
    py::object statistics();
    py::object next() override;
};