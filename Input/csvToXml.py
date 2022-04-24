import pandas as pd

def parser_market_fact_table(row):
    return ("<Insert>\n\t \
    <Column name=\"Ord_id\">%s</Column>\n\t \
    <Column name=\"Prod_id\">%s</Column>\n\t \
    <Column name=\"Ship_id\">%s</Column>\n\t \
    <Column name=\"Cust_id\">%s</Column>\n\t \
    <Column name=\"Sales\">%s</Column>\n\t \
    <Column name=\"Discount\">%s</Column>\n\t \
    <Column name=\"Order_Quantity\">%s</Column>\n\t \
    <Column name=\"Profit\">%s</Column>\n\t \
    <Column name=\"Shipping_Cost\">%s</Column>\n\t \
    <Column name=\"Product_Base_Margin\">%s</Column>\n\t \
    </Insert>" % (row.Ord_id, row.Prod_id, row.Ship_id, row.Cust_id, row.Sales, row.Discount, row.Order_Quantity, 
    row.Profit, row.Shipping_Cost, row.Product_Base_Margin))

def parse_cust_dimension(row):
    return ("<Insert>\n\t \
    <Column name=\"Cust_id\">%s</Column>\n\t \
    <Column name=\"Customer_Name\">%s</Column>\n\t \
    <Column name=\"City\">%s</Column>\n\t \
    <Column name=\"State\">%s</Column>\n\t \
    <Column name=\"Customer_Segment\">%s</Column>\n\t \
    </Insert>" % (row.Cust_id, row.Customer_Name, row.City, row.State, row.Customer_Segment))

def parse_prod_dimension(row):
    return ("<Insert>\n\t \
    <Column name=\"Prod_id\">%s</Column>\n\t \
    <Column name=\"Product_Category\">%s</Column>\n\t \
    <Column name=\"Product_Sub_Category\">%s</Column>\n\t \
    </Insert>" % (row.Prod_id, row.Product_Category, row.Product_Sub_Category))

if __name__ == '__main__':
    # Parse market_fact_table.csv
    df = pd.read_csv("market_fact_table.csv")
    with open("market_fact_table.xml", "w", encoding = "utf-8") as f:
        f.write("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n")
        f.write("<root>\n<Database name = \"marketdb\">\n<Table name = \"market_fact_table\">\n")
        f.write('\n'.join(df.apply(parser_market_fact_table, axis=1)))
        f.write("\n</Table>\n</Database>\n</root>")

    # Parse cust_dimension.csv
    df = pd.read_csv("cust_dimension.csv")
    with open("cust_dimension.xml", "w", encoding = "utf-8") as f:
        f.write("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n")
        f.write("<root>\n<Database name = \"marketdb\">\n<Table name = \"cust_dimension\">\n")
        f.write('\n'.join(df.apply(parse_cust_dimension, axis=1)))
        f.write("\n</Table>\n</Database>\n</root>")

    # Parse prod_dimension.csv
    df = pd.read_csv("prod_dimension.csv")
    with open("prod_dimension.xml", "w", encoding = "utf-8") as f:
        f.write("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n")
        f.write("<root>\n<Database name = \"marketdb\">\n<Table name = \"prod_dimension\">\n")
        f.write('\n'.join(df.apply(parse_prod_dimension, axis=1)))
        f.write("\n</Table>\n</Database>\n</root>")

