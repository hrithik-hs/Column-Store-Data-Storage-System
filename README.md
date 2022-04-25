# Column-Store-Data-Storage-System

Column data storage is a type of NoSQL DBMS that stores data tables by column rather than by row.  The biggest advantage of using this DBMS is to reduce the number of disk accesses (disk reads, writes, seek operations). This DBMS is useful when we want to create a distributed database over many servers. Each server can handle a different column and join operations can be handled by the application itself. This offers more flexibility. It has no fixed schema.

### Uses:
It can be used in ETL operations and data visualization tools just like row databases. Query languages can easily be developed.

### Examples:
Apache Cassandra, HBase, CosmoDB.

### Benchmarks:
Cust_dimension Row Insertion (NoSQL): 0.248s

Market_fact_table Row Insertion (NoSQL): 1.76s 

Prod_dimension Row Insertion (NoSQL): 0.01s

Schema Creation Time (NoSQL): 0.008s

Select.xml (NoSQL): 0.103s

Select profit with discount = 0

  NoSQL: 0.05s

  SQL: 0.37s

Select profit:

  NoSQL: 0.087s

  SQL: 0.03s
