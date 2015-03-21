import java.rmi.registry.*;

public class TaxOfficeClient {
   public static void main (String args[]) {
      try {
         Registry reg = LocateRegistry.getRegistry(1099);
         TaxOfficeInterface t = (TaxOfficeInterface)reg.lookup("rmi://localhost:1099/TaxOffice");
         System.out.print("TaxOffice checks balance of all customers.\n");
         System.out.println("Peter balance: " + t.balanceOfCustomer("Peter"));
         System.out.println("Steve balance: " + t.balanceOfCustomer("Steve"));
         System.out.println("Chris balance: " + t.balanceOfCustomer("Chris"));
         System.out.print("TaxOffice checks numbers of all customers.\n");
         System.out.print("Peter:");
         for (int i : t.numbersOfCustomer("Peter")) {
            System.out.print(" " + i);
         }
         System.out.print("\n");
         System.out.print("Steve:");
         for (int i : t.numbersOfCustomer("Steve")) {
            System.out.print(" " + i);
         }
         System.out.print("\n");
         System.out.print("Chris:");
         for (int i : t.numbersOfCustomer("Chris")) {
            System.out.print(" " + i);
         }
         System.out.print("\n");
         try {
             System.out.print("TaxOffice is trying to get balance of an nonexisting customer\n");
             t.balanceOfCustomer("Tom");
         } catch(BankException e) {
             System.out.print("Exception! ");
             System.out.print(e);
         }
         try {
             System.out.print("TaxOffice is trying to get Accounts of an nonexisting customer\n");
             t.balanceOfCustomer("Tom");
         } catch(BankException e) {
             System.out.print("Exception! ");
             System.out.print(e);
         }
      } catch (Exception e) {
         System.out.println ("ClientException: " + e.getMessage());
      }
   }
}
