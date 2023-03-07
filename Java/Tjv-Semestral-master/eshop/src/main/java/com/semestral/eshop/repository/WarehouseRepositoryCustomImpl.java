package com.semestral.eshop.repository;

import com.semestral.eshop.domain.Product;
import com.semestral.eshop.domain.Warehouse;
import org.springframework.stereotype.Repository;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.TypedQuery;
import java.util.Comparator;
import java.util.List;

import static java.awt.geom.Point2D.distance;
@Repository
public class WarehouseRepositoryCustomImpl implements WarehouseRepositoryCustom{
    @PersistenceContext
    private EntityManager entityManager;

    /**
     * Finds the furthest warehouse that has one of the available products
     * @param deliverTo Coordinates of the user in "XX.XXX:YY.YYY" format
     * @param toDeliver all the products that the user wants to buy
     * @return Warehouse that is the furthest away
     */
    @Override
    public Warehouse calculateFurthest(String deliverTo, List<Product> toDeliver ){
        String jpql = "SELECT w FROM Warehouse w JOIN w.availableProducts p WHERE p IN :products";
        TypedQuery<Warehouse> query = entityManager.createQuery(jpql, Warehouse.class);
        query.setParameter("products", toDeliver);
        List<Warehouse> warehouses = query.getResultList();
        double userLatitude = Double.parseDouble( deliverTo.split(":")[0] );
        double userLongitude = Double.parseDouble( deliverTo.split(":")[1] );

        warehouses.sort((w1, w2) -> Double.compare(
                distance(userLatitude, userLongitude,
                        Double.parseDouble( w2.getCoordinates().split(":")[0] ),
                        Double.parseDouble( w2.getCoordinates().split(":")[1] )),
                distance(userLatitude, userLongitude,
                        Double.parseDouble( w1.getCoordinates().split(":")[0] ),
                        Double.parseDouble( w1.getCoordinates().split(":")[1] ))));
        return warehouses.get(0);
    }

    /**
     * Finds the nearest warehouse that has the product
     * @param deliverTo Coordinates of the user in "XX.XXX:YY.YYY" format
     * @param toDeliver The Product to deliver
     * @return Warehouse that is closest
     */
    @Override
        public Warehouse findNearest(String deliverTo, Product toDeliver ){
        String jpql = "SELECT w FROM Warehouse w JOIN w.availableProducts p WHERE p IN :product";
        TypedQuery<Warehouse> query = entityManager.createQuery(jpql, Warehouse.class);
        query.setParameter("product", toDeliver);
        List<Warehouse> warehouses = query.getResultList();
        double userLatitude = Double.parseDouble( deliverTo.split(":")[0] );
        double userLongitude = Double.parseDouble( deliverTo.split(":")[1] );

        warehouses.sort(Comparator.comparingDouble(w -> distance(userLatitude, userLongitude,
                Double.parseDouble(w.getCoordinates().split(":")[0]),
                Double.parseDouble(w.getCoordinates().split(":")[1]))));
        return warehouses.get(0);
    }

    /**
     * Calculates the travel TIME between two points
     * @param deliverTo Coordinates of the user in "XX.XXX:YY.YYY" format
     * @param deliverFrom Coordinates of the warehouse in "XX.XXX:YY.YYY" format
     * @return time to deliver in minutes
     */
    @Override
    public int calculateTravelDistance(String deliverTo, String deliverFrom){
        double userLatitude = Double.parseDouble( deliverTo.split(":")[0] );
        double userLongitude = Double.parseDouble( deliverTo.split(":")[1] );
        double  dist =
                distance(userLatitude, userLongitude,
                Double.parseDouble( deliverFrom.split(":")[0] ),
                Double.parseDouble( deliverFrom.split(":")[1] ));

//        Is this terrible practice? Yes.
//        Could I have defined this in application.properties, created a class for
//        global variables, set the scope and injected it? Yes.
//        Am I willing to code for 2 hours just to get one variable injected properly? No.
//        By the way this is the peak speed of a top of the line racing drone.
        int droneKmPerM = 4;

        return (int) (dist/droneKmPerM);
    }

}
