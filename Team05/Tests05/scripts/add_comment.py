import xml.etree.ElementTree as ET

# Parse the input XML file
tree = ET.parse('out.xml')
root = tree.getroot()

# Loop through each <query> element
for query in root.findall('.//query'):
    # Check if there is an <id> element
    if query.find('id') is not None:
        # Add a "comment" attribute with some text
        query.set('comment', 'smth')

# Write the updated XML to a new file
tree.write('output.xml')