package ru.servers.resourceserver;

import org.junit.Assert;
import org.junit.Test;
import ru.servers.resourceserver.osmexception.InvalidOSMDataException;

public class OSMMinifierTest {

    private OSMMinifier osmMinifier = new OSMMinifier();

    @Test // deleting attributes in tag node
    public void checkingNodeMinification() throws InvalidOSMDataException {

         String sourceData =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?> " +
            "<osm attribution=\"http://www.openstreetmap.org/copyright\" copyright=\"OpenStreetMap and contributors\" generator=\"CGImap 0.6.1 (11633 thorn-03.openstreetmap.org)\" license=\"http://opendatacommons.org/licenses/odbl/1-0/\" version=\"0.6\">" +
                 "<node id=\"229895281\" visible=\"true\" version=\"9\" changeset=\"6533528\" timestamp=\"2010-12-04T00:25:23Z\" user=\"luiswoo\" uid=\"311318\" lat=\"47.0748911\" lon=\"39.3228292\"/>" +
            "</osm>";
         String minifiedData =
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?> " +
                        "<osm attribution=\"http://www.openstreetmap.org/copyright\" copyright=\"OpenStreetMap and contributors\" generator=\"CGImap 0.6.1 (11633 thorn-03.openstreetmap.org)\" license=\"http://opendatacommons.org/licenses/odbl/1-0/\" version=\"0.6\">" +
                 "<node id=\"229895281\" lat=\"47.0748911\" lon=\"39.3228292\"/>" +
            "</osm>";

        String resultMinification = osmMinifier.minify(sourceData);
        minifiedData = normalizationMinifiedData(minifiedData);
        resultMinification = normalizationResultMinification(resultMinification);
        Assert.assertEquals(minifiedData, resultMinification);
    }

    @Test // deleting attributes in tag way
    public void checkingWayMinification() throws InvalidOSMDataException {

        String sourceData =
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?> " +
                        "<osm attribution=\"http://www.openstreetmap.org/copyright\" copyright=\"OpenStreetMap and contributors\" generator=\"CGImap 0.6.1 (11633 thorn-03.openstreetmap.org)\" license=\"http://opendatacommons.org/licenses/odbl/1-0/\" version=\"0.6\">" +
                        "<way id=\"580429971\" visible=\"true\" version=\"1\" changeset=\"58135270\" timestamp=\"2018-04-16T11:43:32Z\" user=\"Alex_Enot\" uid=\"5757927\"></way>" +
                        "</osm>";
        String minifiedData =
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?> " +
                        "<osm attribution=\"http://www.openstreetmap.org/copyright\" copyright=\"OpenStreetMap and contributors\" generator=\"CGImap 0.6.1 (11633 thorn-03.openstreetmap.org)\" license=\"http://opendatacommons.org/licenses/odbl/1-0/\" version=\"0.6\">" +
                        "<way id=\"580429971\"/>" +
                        "</osm>";

        String resultMinification = osmMinifier.minify(sourceData);
        minifiedData = normalizationMinifiedData(minifiedData);
        resultMinification = normalizationResultMinification(resultMinification);
        Assert.assertEquals(minifiedData, resultMinification);
    }

    @Test // deleting attributes in tag relation
    public void checkingRelationMinification() throws InvalidOSMDataException {

        String sourceData =
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?> " +
                        "<osm attribution=\"http://www.openstreetmap.org/copyright\" copyright=\"OpenStreetMap and contributors\" generator=\"CGImap 0.6.1 (11633 thorn-03.openstreetmap.org)\" license=\"http://opendatacommons.org/licenses/odbl/1-0/\" version=\"0.6\">" +
                        "<relation id=\"5848537\" visible=\"true\" version=\"5\" changeset=\"58135270\" timestamp=\"2018-04-16T11:43:37Z\" user=\"Alex_Enot\" uid=\"5757927\"/>" +
                        "</osm>";
        String minifiedData =
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?> " +
                        "<osm attribution=\"http://www.openstreetmap.org/copyright\" copyright=\"OpenStreetMap and contributors\" generator=\"CGImap 0.6.1 (11633 thorn-03.openstreetmap.org)\" license=\"http://opendatacommons.org/licenses/odbl/1-0/\" version=\"0.6\">" +
                        "<relation id=\"5848537\"/>" +
                        "</osm>";

        String resultMinification = osmMinifier.minify(sourceData);
        minifiedData = normalizationMinifiedData(minifiedData);
        resultMinification = normalizationResultMinification(resultMinification);
        Assert.assertEquals(minifiedData, resultMinification);
    }

    @Test(expected = InvalidOSMDataException.class) // minification invalid string osmData
    public void checkingInvalidStringMinification() throws InvalidOSMDataException {

        final String sourceData =
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?> " +
                        "<osm attribution=\"http://www.openstreetmap.org/copyright\" copyright=\"OpenStreetMap and contributors\" generator=\"CGImap 0.6.1 (11633 thorn-03.openstreetmap.org)\" license=\"http://opendatacommons.org/licenses/odbl/1-0/\" version=\"0.6\">" +
                        "<way id=\"580429971\" visible=\"true\" version=\"1\" changeset=\"58135270\" timestamp=\"2018-04-16T11:43:32Z\" user=\"Alex_Enot\" uid=\"5757927\"></way>";
        final String minifiedData = "";

        String resultMinification = osmMinifier.minify(sourceData);
        Assert.assertEquals(minifiedData, resultMinification);
    }

    @Test(expected = InvalidOSMDataException.class) // minification empty string osmData
    public void checkingEmptyStringMinification() throws InvalidOSMDataException {

        final String sourceData = "";
        final String minifiedData = "";

        String resultMinification = osmMinifier.minify(sourceData);
        Assert.assertEquals(minifiedData, resultMinification);
    }

    private String normalizationMinifiedData(String minifiedData) {
        minifiedData = minifiedData.replaceAll("\\s", "");
        minifiedData = minifiedData.replaceAll("\\t", "");
        minifiedData = minifiedData.replaceAll("\\n", "");
        return minifiedData;
    }

    private String normalizationResultMinification(String resultMinification) {
        resultMinification = resultMinification.replaceAll("\\s","");
        resultMinification = resultMinification.replaceAll("\\t","");
        resultMinification = resultMinification.replaceAll("\\n","");
        return resultMinification;
    }
}