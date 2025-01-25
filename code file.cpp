#include<stdio.h>
#include<string.h>
struct product
{
	int id;
	char name[100];
	int quantity;
	int price;
	int discount;
};

struct voucher
{
	char voucherno[100];
	int discount;
	int min;
};

struct card
{
	char name[100];
	int discount;
	int discountlimit;
};
void addproduct()
{
	struct product p;
	FILE * ptr;
	ptr = fopen("product.txt","a");
	printf("enter the product id : ");
	scanf("%d",&p.id);
	printf("enter the product name : ");
	scanf("%s",p.name);
	printf("enter the quantity of the product available :");
	scanf("%d",&p.quantity);
	printf("enter the price of product : ");
	scanf("%d",&p.price);
	printf("enter the discount percentage applied to the product.If no discount then enter 0 :");
	scanf("%d",&p.discount);
	size_t result = fwrite(&p, sizeof(struct product), 1, ptr);
	fclose(ptr);
}

void addvoucher()
{
	struct voucher v;
	FILE * ptr;
	ptr = fopen("voucher.txt","ab");
	
	printf("enter the voucher number : ");
	scanf("%s",v.voucherno);
	printf("enter the discount applied : ");
	scanf("%d",&v.discount);
	printf("enter the minimum amount : ");
	scanf("%d",&v.min);
	size_t result = fwrite(&v, sizeof(struct voucher), 1, ptr);
	fclose(ptr);
}

void addcard()
{
	struct card c;
	FILE * ptr;
	ptr = fopen("card.txt","ab");
	printf("enter the name of card :");
	scanf("%s",c.name);
	printf("enter the dicount available on the card.if no discount then enter 0 : ");
	scanf("%d",&c.discount);
	printf("enter the discount limit\cap : ");
	scanf("%d",&c.discountlimit);
	size_t result = fwrite(&c, sizeof(struct card), 1, ptr);
	fclose(ptr);
}

float calculateproduct() {
    int count = 0;
    int userid;
    struct product cpyproduct, cpy[100];
    int flag = 0;
    float total = 0.00;
    
    FILE *ptr;
    FILE *tempfile;

    while (1) {  // Trip value of the userid is -1 to end the loop
        ptr = fopen("product.txt", "rb");
        tempfile = fopen("temp.txt", "wb");

        if (ptr == NULL || tempfile == NULL) {
            printf("Error opening file.\n");
            return 0.0;
        }

        printf("Enter the ID of the product (-1 to stop): ");
        scanf("%d", &userid);

        if (userid == -1) {
            
            remove("product.txt");
            rename("temp.txt", "product.txt");
            fclose(ptr);
            fclose(tempfile);
            
           
            break;
        }

        rewind(ptr); 
        flag = 0;

        while (fread(&cpyproduct, sizeof(struct product), 1, ptr)) {
            if (userid == cpyproduct.id) {
                if (cpyproduct.quantity > 0) {
                    cpyproduct.quantity--;
                    printf("Quantity remaining: %d\n", cpyproduct.quantity);

                    cpy[count] = cpyproduct; 
                    count++;
                    flag = 1;
                    printf("Product added to the cart successfully.\n");
                } else {
                    printf("Product out of stock.\n");
                }
            }
   
            fwrite(&cpyproduct, sizeof(struct product), 1, tempfile);
        }

        if (flag == 0) {
            printf("Product not found. Please try again.\n");
        }

        fclose(ptr);
        fclose(tempfile);
        remove("product.txt");
        rename("temp.txt", "product.txt");
    }

    int i;
    printf("\n");
    printf("ID              Name             Price          Discount (%)      Discounted Price\n");
    for ( i = 0; i < count; i++) {
        float discountedPrice = cpy[i].price * (1.0 - (cpy[i].discount / 100.0));
        total += discountedPrice;

        printf("%-8d       %-8s        %-12d        %-12d             %-12.2f\n",
               cpy[i].id, cpy[i].name, cpy[i].price, cpy[i].discount, discountedPrice);
    }

    printf("\n");
    printf("Total amount is: %.2f\n", total);
    return total;
}


float calculatevoucher(float total)
{
	int voucherdiscount = 0,found = 0;
	struct voucher cpyvoucher,cpy;
	char uservouch[100];
	char userans;
	FILE * ptr;
	printf("do you want to add voucher yes/no(y/n) : ");
	scanf(" %c",&userans);
	if(userans == 'Y' || userans == 'y')
	{
		printf("enter the voucher no : ");
		scanf("%s",uservouch);
		uservouch[strcspn(uservouch, "\n")] = '\0';

		ptr = fopen("voucher.txt","rb");
		while(fread(&cpyvoucher, sizeof(struct voucher), 1, ptr))
		{
			cpy = cpyvoucher;
			

			if (strcmp(cpy.voucherno, uservouch) == 0)
			{
				
				if(total > cpy.min)
				{
					voucherdiscount = cpy.discount;
					total = total - cpy.discount;
					found = 1;
					printf("voucher added to the cart\n");
					printf("voucher discount : %d\n",voucherdiscount);
				}
				else
				{
					printf("minimum amount not reached \n ");
					found = 1;
				}
			}
		}
		if(found == 0)
		{
			printf("invalid voucher\n");
		}
	
		found = 0;
		fclose(ptr);
	
	}
	return total;
}
float calculatecard(float total)
{
		struct card cpycard;
		struct card cpy;
		char bankname[100];
		float discount ;
		int found = 0;
		FILE * ptr;
		ptr = fopen("card.txt","rb");
		printf("enter the bank name : ");
		scanf("%s",bankname);
				while(fread(&cpycard, sizeof(struct card), 1, ptr))
				{
					
					cpy = cpycard;
					
					if (strcmp(cpy.name, bankname) == 0)
					{
						discount= total * (cpy.discount /100.0);
						if(discount < cpy.discountlimit)
						{

							
							total = total *(1.00-(cpy.discount/100.00));
							printf("card discount applied successfully with a discount of %d percent \n",cpy.discount);
						
							found = 1;
						}
						else
						{
							discount = cpy.discountlimit;
							total = total - cpy.discountlimit;
							found = 1;
							printf("discount limit crossed\n");
						}
					}
				}
				if(found == 0)
				{
					printf("no discount available on this card\n");
				}
		
			printf("card discount = %f\n",discount);
			return total;
}
	
		
	
	
	
	
	


int main()
{

	int flag = 0;
	char ans;
	int user;
	printf("*******VENDOR MANAGEMENT SYSTEM*******\n");
	while(flag == 0)
	{
		printf("do you want to add the product yes/no(y/n): ");
		scanf(" %c",&ans);
		if(ans == 'y' || ans == 'Y')
		{
			addproduct();
		}
		else
		{
			flag = 1;
		}

	}
		
		while(flag == 1)
		{
			printf("do you want to add the voucher yes/no(y/n): ");
			scanf(" %c",&ans);
			
			if(ans == 'y' || ans == 'Y')
			{
				addvoucher();
			}
			else 
			{
				flag = 0;
			}
		
			
		}
		
		while(flag == 0)
		{
			
		printf("do you want to add card (y/n): ");
		scanf(" %c",&ans);
		if(ans == 'y' || ans == 'Y')
		{
			addcard();
		}
		else 
		{
			flag = 1;
		}

		}
	printf("****************************************************************************************************************************************************************************\n");	
	printf("****CUSTOMER MANAGEMENT SYSYTEM*****\n");
	float total,cash;
	total = calculateproduct();
	total = calculatevoucher(total);
	printf("do you want to pay through card/cash(1/0)");
	scanf("%d",&user);
	if(user == 1)
	{
	
	total = calculatecard(total);
	printf("Grand Total : %f",total);
	}
	else
	{
		printf("Grand Total : %f\n",total);
		printf("Please enter the cash amount given by the customer: ");
		scanf("%f",&cash);
		printf("change amount : %f",(cash-total));
		
	}

}

