#ifndef DMGDISK_H
#define DMGDISK_H
#include "PartitionedDisk.h"
#include "Reader.h"
#include "dmg.h"
#include <libxml/parser.h>
#include <libxml/xpath.h>

class DMGDisk : public PartitionedDisk
{
public:
	DMGDisk(Reader* reader);
	~DMGDisk();

	virtual const std::vector<Partition>& partitions() const { return m_partitions; }
	virtual Reader* readerForPartition(int index) override;

	static bool isDMG(Reader* reader);
private:
	void loadKoly(const UDIFResourceFile& koly);
	bool loadPartitionElements(xmlXPathContextPtr xpathContext, xmlNodeSetPtr nodes);
	static bool parseNameAndType(const std::string& nameAndType, std::string& name, std::string& type);
	static bool base64Decode(const std::string& input, std::vector<uint8_t>& output);
	BLKXTable* loadBLKXTableForPartition(int index);
	Reader* readerForKolyBlock(int index);
private:
	Reader* m_reader;
	std::vector<Partition> m_partitions;
	xmlDocPtr m_kolyXML;
	int m_blkxBlocks;
};

#endif

