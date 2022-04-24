import pandas as pd

def parser_market_fact_table(row):
    return ("<input>\n\t \
    <Ord_id>%s</Ord_id>\n\t \
    <Prod_id>%s</Prod_id>\n\t \
    <Ship_id>%s</Ship_id>\n\t \
    <Cust_id>%s</Cust_id>\n\t \
    <Sales>%s</Sales>\n\t \
    <Discount>%s</Discount>\n\t \
    <Order_Quantity>%s</Order_Quantity>\n\t \
    <Profit>%s</Profit>\n\t \
    <Shipping_Cost>%s</Shipping_Cost>\n\t \
    <Product_Base_Margin>%s</Product_Base_Margin>\n \
    </input>" % (row.Ord_id, row.Prod_id, row.Ship_id, row.Cust_id, row.Sales, row.Discount, row.Order_Quantity, 
    row.Profit, row.Shipping_Cost, row.Product_Base_Margin))

def parse_cust_dimension(row):
    return ("<input>\n\t \
    <Cust_id>%s<\Cust_id>\n\t \
    <Customer_Name>%s<\Customer_Name>\n\t \
    <City>%s<\City>\n\t \
    <State>%s<\State>\n\t \
    <Customer_Segment>%s<\Customer_Segment>\n \
    <\input>" % (row.Cust_id, row.Customer_Name, row.City, row.State, row.Customer_Segment))

def parse_prod_dimension(row):
    return ("<input>\n\t \
    <Prod_id>%s<\Prod_id>\n\t \
    <Product_Category>%s<\Product_Category>\n\t \
    <Product_Sub_Category>%s<\Product_Sub_Category>\n \
    <\input>" % (row.Prod_id, row.Product_Category, row.Product_Sub_Category))

if __name__ == '__main__':
    # Parse market_fact_table.csv
    df = pd.read_csv("market_fact_table.csv")
    with open("market_fact_table.xml", "w", encoding = "utf-8") as f:
        f.write("<?xml version=\"1.0\" encoding=\"utf-8\">\n")
        f.write("<root>\n<Database name = \"marketdb\">\n<Table name = \"market_fact_table\">\n")
        f.write('\n'.join(df.apply(parser_market_fact_table, axis=1)))
        f.write("\n<\Table>\n<\Database>\n<\\root>")

    # Parse cust_dimension.csv
    df = pd.read_csv("cust_dimension.csv")
    with open("cust_dimension.xml", "w", encoding = "utf-8") as f:
        f.write("<?xml version=\"1.0\" encoding=\"utf-8\">\n")
        f.write("<root>\n<Database name = \"marketdb\">\n<Table name = \"cust_dimension\">\n")
        f.write('\n'.join(df.apply(parse_cust_dimension, axis=1)))
        f.write("\n<\Table>\n<\Database>\n<\\root>")

    # Parse prod_dimension.csv
    df = pd.read_csv("prod_dimension.csv")
    with open("prod_dimension.xml", "w", encoding = "utf-8") as f:
        f.write("<?xml version=\"1.0\" encoding=\"utf-8\">\n")
        f.write("<root>\n<Database name = \"marketdb\">\n<Table name = \"prod_dimension\">\n")
        f.write('\n'.join(df.apply(parse_prod_dimension, axis=1)))
        f.write("\n<\Table>\n<\Database>\n<\\root>")
