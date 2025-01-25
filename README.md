# Programming Fundamental-project
### Vendor and Customer Management System

The Vendor and Customer Management System is a comprehensive software solution designed to assist vendors in managing their inventory, discounts, vouchers, and bank card offers while allowing customers to perform seamless shopping and payment activities. The system is developed using the C programming language, utilizing **structures**, **file handling**, and a **modular programming approach** to ensure efficiency, scalability, and user-friendliness. This report provides a detailed overview of the various functions implemented in the system.

---

### Vendor Management

The vendor management functionalities focus on allowing vendors to add products, create vouchers, and define discount card schemes. The addproduct() function enables vendors to add new products to the inventory. It collects essential product details, including the product ID, name, available quantity, price, and applicable discount percentage. The information is stored in a binary file, `product.txt`, using the `fwrite()` function, ensuring persistent storage. This allows the system to dynamically track product details for subsequent customer interactions.

Similarly, the addvoucher() function allows vendors to create promotional vouchers. Vendors can specify the voucher number, discount amount, and the minimum purchase amount required to use the voucher. These details are stored in a binary file, `voucher.txt`. This feature provides flexibility in marketing strategies, as vouchers can be customized for specific purchase thresholds. 

The addcard() function focuses on defining bank-specific discount cards. Vendors can specify the bank name, discount percentage, and a maximum discount limit for each card. This data is saved in the `card.txt` file, allowing the system to later validate and apply card-based discounts during customer transactions. By offering discounts through specific bank cards, vendors can encourage customers to use particular payment methods, increasing collaboration with banking institutions.

---

### Customer Management

The customer management module is designed to handle the selection of products, application of discounts, and payment processing. The calculateproduct() function allows customers to select products by entering their product IDs. The function retrieves the product details from the inventory, checks for availability, and reduces the stock quantity accordingly. It dynamically calculates the total cost of selected products, applying any product-specific discounts. The system also ensures that the product inventory is updated in real-time by using a temporary file to reflect the reduced quantities.

The calculatevoucher() function provides customers the option to apply vouchers during checkout. By inputting the voucher number, the system checks its validity against the stored vouchers in `voucher.txt`. If the voucher is valid and the total purchase amount exceeds the minimum requirement, the discount is applied. This function handles scenarios where the voucher is invalid or the conditions are not met, ensuring clear communication with the customer.

The calculatecard() function further enhances the customer experience by applying discounts based on bank cards. Customers enter the bank name, and the system retrieves the card details from `card.txt`. The discount is calculated as a percentage of the total purchase amount, capped by the maximum discount limit defined for the card. If no matching card is found or if the discount conditions are not met, the system provides appropriate feedback to the customer.

Finally, the system offers flexible payment options through the main function. Customers can choose between cash and card payment methods. For cash payments, the system calculates and displays the change to be returned. For card payments, the applicable bank card discount is applied before displaying the final total. This functionality ensures a smooth and efficient checkout process.

---


### Conclusion

The Vendor and Customer Management System is a robust solution for managing product inventories, discounts, and payments. Its modular design, efficient use of file handling, and clear user interaction make it a valuable tool for both vendors and customers. By integrating multiple discount mechanisms and offering flexible payment options, the system ensures a seamless and rewarding experience for all stakeholders. This project serves as a foundation for further enhancements, such as user authentication, advanced reporting, and support for additional payment methods.

