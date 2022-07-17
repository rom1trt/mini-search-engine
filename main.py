from asyncore import write
from mongo import *

def write_on_db(doc_file_path: str, db_name: str, collection_name: str):
    database1 = DB(db_name)
    print("Database created")
    database1.post_db(doc_file_path, collection_name)
    print("Text file stored on database")

write_on_db("datasets/bigDataset.txt", "test_db", "test_collection")